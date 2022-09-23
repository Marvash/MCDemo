#pragma once
#include "Block.h"

class BlockManager;
class ItemHandle;

class BlockBreakingContext {
public:
	BlockBreakingContext(BlockManager* blockManager);
	void stopBreaking();
	void updateBreaking(double delta, Block* block, ItemHandle* itemUsed);
private:
	void startBreaking(Block* block, ItemHandle* itemUsed);
	void updateCurrentContext(double delta);

	bool m_active;
	float m_cumulativeTime;
	float m_requiredTimeInSeconds;
	Block* m_involvedBlock;
	ItemHandle* m_itemUsed;
	BlockManager* m_blockManager;
};