#include "BlockManager.h"

BlockManager::BlockManager(CoreEventDispatcher* coreEventDispatcher) : 
	m_blockBreakingContext(new BlockBreakingContext(this)) {

}

void BlockManager::onNotify(Event& newEvent) {

}

void BlockManager::notify(Event& newEvent) {

}

void BlockManager::init(BlockLibrary* blockLibrary) {
	m_blockLibrary = blockLibrary;
}

void BlockManager::breakBlock(ItemHandle* itemUsed, Block* toBreak) {
	DroppableBlockSharedSpec* droppableSpec = m_blockLibrary->getDroppableBlockSpecification(toBreak->getBlockId());
	droppableSpec->dropBlock(itemUsed, toBreak);
	changeBlock(toBreak, BlockId::AIR);
}

void BlockManager::changeBlock(Block* block, BlockId blockId) {
	block->m_blockId = blockId;
	Chunk* parentChunk = block->getChunkRef();
}

std::string& BlockManager::getDisplayName(BlockId blockId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->getDisplayName();
}

bool BlockManager::isTransparent(BlockId blockId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->isTransparent();
}

bool BlockManager::isRenderable(BlockId blockId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->isRenderable();
}

ItemId BlockManager::getBlockItemId(BlockId blockId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->getBlockItemId();
}

float BlockManager::getBlockHardness(BlockId blockId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->getBlockHardness();
}

bool BlockManager::isWeakTo(BlockId blockId, ItemId itemId) const {
	return m_blockLibrary->getBlockSpecification(blockId)->isWeakTo(itemId);
}

void BlockManager::updateBlockBreakingContext(double delta, Block* block, ItemHandle* itemUsed) {
	m_blockBreakingContext->updateBreaking(delta, block, itemUsed);
}

void BlockManager::stopBlockBreakingContext() {
	m_blockBreakingContext->stopBreaking();
}

bool BlockManager::getIsBreakingBlock() {
	return m_blockBreakingContext->getIsBreakingBlock();
}

bool BlockManager::isBlockBeingBroken(Block* block) {
	return m_blockBreakingContext->getIsBreakingBlock() && m_blockBreakingContext->getBreakingBlock() == block;
}

BlockBreakingContext::BlockBreakStage BlockManager::getBreakingStage() {
	return m_blockBreakingContext->getBreakingStage();
}