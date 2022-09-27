#pragma once
#include "Block.h"

class BlockManager;
class ItemHandle;

class BlockBreakingContext {
public:
	enum class BlockBreakStage {
		BREAKPROGRESS0,
		BREAKPROGRESS1,
		BREAKPROGRESS2,
		BREAKPROGRESS3,
		BREAKPROGRESS4,
		BREAKPROGRESS5,
		BREAKPROGRESS6,
		BREAKPROGRESS7,
		BREAKPROGRESS8,
		BREAKPROGRESS9,
		BREAKPROGRESS10
	};

	BlockBreakingContext(BlockManager* blockManager);
	bool getIsBreakingBlock();
	BlockBreakStage getBreakingStage();
	Block* getBreakingBlock();
	void stopBreaking();
	void updateBreaking(double delta, Block* block, ItemHandle* itemUsed);
private:
	void startBreaking(Block* block, ItemHandle* itemUsed);
	void updateCurrentContext(double delta);
	void updateBlockBreakingStage();

	bool m_active;
	float m_cumulativeTime;
	float m_requiredTimeInSeconds;
	Block* m_involvedBlock;
	ItemHandle* m_itemUsed;
	BlockManager* m_blockManager;
	BlockBreakStage m_currentBreakingStage;
};