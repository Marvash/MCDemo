#pragma once
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "Core/Services/BlockLibrary/Block.h"
#include <vector>

class CoreServiceLocator;
class Inventory;

class DroppableBlockSharedSpec {

	friend class BlockLibrary;

public:
	DroppableBlockSharedSpec();
	Inventory* getInventory();
	ItemId getDroppedItem();

	int getDroppedCount();
	bool canBeDroppedByItem(ItemId itemUsed);
	void dropBlock(ItemHandle* itemUsed, Block* toBreak);
private:
	std::vector<ItemId> m_exclusiveItemDropList;
	ItemId m_droppedItem;
	CoreServiceLocator* m_coreServiceLocator;
	int m_droppedCount;
};