#include "BlockBreakingContext.h"
#include "BlockManager.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"

BlockBreakingContext::BlockBreakingContext(BlockManager* blockManager) :
	m_active(false),
	m_cumulativeTime(0.0f),
	m_requiredTimeInSeconds(0.0f),
	m_involvedBlock(nullptr),
	m_blockManager(blockManager) {

}

void BlockBreakingContext::startBreaking(Block* block, ItemHandle* itemUsed) {
	m_active = true;
	m_cumulativeTime = 0.0f;
	m_involvedBlock = block;
	m_itemUsed = itemUsed;
	float scalingFactor = 1.0f;
	if (m_blockManager->isWeakTo(m_involvedBlock->getBlockId(), m_itemUsed->getItemId())) {
		scalingFactor = itemUsed->getItemBreakScalingFactor();
		BOOST_LOG_TRIVIAL(info) << "SCALING FACTOR CHANGED " << scalingFactor;
	}
	m_requiredTimeInSeconds = m_blockManager->getBlockHardness(block->getBlockId()) * scalingFactor;
}

void BlockBreakingContext::stopBreaking() {
	m_active = false;
	m_cumulativeTime = 0.0f;
	m_involvedBlock = nullptr;
	m_itemUsed = nullptr;
}

void BlockBreakingContext::updateBreaking(double delta, Block* block, ItemHandle* itemUsed) {
	if (m_active && block == m_involvedBlock && itemUsed == m_itemUsed) {
		updateCurrentContext(delta);
	} else {
		startBreaking(block, itemUsed);
	}
}

void BlockBreakingContext::updateCurrentContext(double delta) {
	m_cumulativeTime += static_cast<float>(delta);
	if (m_cumulativeTime >= m_requiredTimeInSeconds) {
		m_blockManager->breakBlock(m_itemUsed, m_involvedBlock);
		m_involvedBlock->getChunkRef()->forceChunkMeshUpdate();
		stopBreaking();
	}
}