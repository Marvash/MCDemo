#pragma once
#include "Core/Cube/Cube.h"
#include "Item.h"
#include <vector>

class InventoryManager {
public:
	InventoryManager();
	~InventoryManager();
private:
	const unsigned int ITEMBAR_SLOTS = 10;

	unsigned int m_selectedSlot;
	Item* m_itemBar;
};