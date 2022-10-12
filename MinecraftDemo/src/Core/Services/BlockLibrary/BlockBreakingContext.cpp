#include "BlockBreakingContext.h"
#include "BlockManager.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"

BlockBreakingContext::BlockBreakingContext(BlockManager* blockManager) :
	m_active(false),
	m_cumulativeTime(0.0f),
	m_requiredTimeInSeconds(0.0f),
	m_involvedBlock(nullptr),
	m_blockManager(blockManager),
	m_currentBreakingStage(BlockBreakingContext::BlockBreakStage::BREAKPROGRESS0) {

}

bool BlockBreakingContext::getIsBreakingBlock() {
	return m_active;
}

BlockBreakingContext::BlockBreakStage BlockBreakingContext::getBreakingStage() {
	return m_currentBreakingStage;
}

Block* BlockBreakingContext::getBreakingBlock() {
	return m_involvedBlock;
}

void BlockBreakingContext::startBreaking(Block* block, ItemHandle* itemUsed) {
	m_active = true;
	m_cumulativeTime = 0.0f;
	m_involvedBlock = block;
	m_itemUsed = itemUsed;
	float scalingFactor = 1.0f;
	if (m_blockManager->isWeakTo(m_involvedBlock->getBlockId(), m_itemUsed->getItemId())) {
		scalingFactor = itemUsed->getItemBreakScalingFactor();
	}
	m_requiredTimeInSeconds = m_blockManager->getBlockHardness(block->getBlockId()) * scalingFactor;
}

void BlockBreakingContext::stopBreaking() {
	//BOOST_LOG_TRIVIAL(info) << "STOPPING BREAKING CONTEXT 2";
	if (m_active) {
		m_active = false;
		m_cumulativeTime = 0.0f;
		m_involvedBlock->getChunkRef()->forceChunkMeshUpdate();
		m_involvedBlock = nullptr;
		m_itemUsed = nullptr;
		m_currentBreakingStage = BlockBreakingContext::BlockBreakStage::BREAKPROGRESS0;
	}
}

void BlockBreakingContext::updateBreaking(double delta, Block* block, ItemHandle* itemUsed) {
	//BOOST_LOG_TRIVIAL(info) << "UPDATING BREAKING CONTEXT 2";
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
	if (m_active) {
		updateBlockBreakingStage();
	}
}

void BlockBreakingContext::updateBlockBreakingStage() {
	float breakingPercentageProgress = m_cumulativeTime / m_requiredTimeInSeconds;
	int progressLevels = static_cast<int>(BlockBreakingContext::BlockBreakStage::BREAKPROGRESS10);
	int intBlockBreakProgress = static_cast<int>(breakingPercentageProgress * progressLevels);
	BlockBreakingContext::BlockBreakStage newStage = static_cast<BlockBreakingContext::BlockBreakStage>(intBlockBreakProgress);
	if (newStage != m_currentBreakingStage) {
		m_currentBreakingStage = newStage;
		m_involvedBlock->getChunkRef()->forceChunkMeshUpdate();
	}
}