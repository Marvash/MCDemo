#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/BlockLibrary/BlockLibrary.h"
#include "BlockBreakingContext.h"
#include "Core/Chunk/Chunk.h"
#include "Block.h"

class BlockManager : CoreService {

friend class Block;

public:
	BlockManager(CoreEventDispatcher* coreEventDispatcher);
	void onNotify(Event& newEvent) override;
	void notify(Event& newEvent) override;
	void init(BlockLibrary* m_blockLibrary);
	void breakBlock(ItemHandle* itemUsed, Block* toBreak);
	std::string& getDisplayName(BlockId blockId) const;
	bool isTransparent(BlockId blockId) const;
	bool isRenderable(BlockId blockId) const;
	ItemId getBlockItemId(BlockId blockId) const;
	float getBlockHardness(BlockId blockId) const;
	bool isWeakTo(BlockId blockId, ItemId itemId) const;
	void updateBlockBreakingContext(double delta, Block* block, ItemHandle* itemUsed);
	void stopBlockBreakingContext();
	bool getIsBreakingBlock();
	bool isBlockBeingBroken(Block* block);
	BlockBreakingContext::BlockBreakStage getBreakingStage();
private:
	void changeBlock(Block* block, BlockId blockId);

	BlockLibrary* m_blockLibrary;
	BlockBreakingContext* m_blockBreakingContext;
};