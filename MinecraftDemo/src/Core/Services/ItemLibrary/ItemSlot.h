#pragma once
#include "Item.h"

class ItemSlot {
public:
	ItemSlot();
	~ItemSlot();
	void swapItemSlot(ItemSlot* itemSlot);
	void mergeItemSlot(ItemSlot* itemSlot);
	void resolveSlotDrag(ItemSlot* itemSlot);
	void decreaseItemCountBy(int count);
	void increaseItemCountBy(int count);
	Item* getItem();
	Item* takeItem();
	void replaceItem(Item* item);
	void resetItem();
	bool isEmpty();
	bool checkMergeCompatibility(ItemSlot* itemSlot);

private:
	Item* m_item;
};