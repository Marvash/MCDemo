#pragma once
#include "Core/Cube/Cube.h"
#include "Item.h"
#include "CubeItem.h"
#include <glm/glm.hpp>
#include <vector>

class InventoryManager {
public:
	InventoryManager();
	~InventoryManager();

	int queryItemSpace(Cube::CubeId cubeId);
	int queryItem(Cube::CubeId cubeId);
	void addItem(Cube::CubeId cubeId, unsigned int count);
	void removeItem(Cube::CubeId cubeId, unsigned int count);
	void addItemInInventorySlot(Cube::CubeId cubeId, unsigned int count, unsigned int slot);
	void removeItemInInventorySlotCount(Cube::CubeId cubeId, unsigned int count, unsigned int slot);
	void removeItemInInventorySlot(unsigned int slot);
	void swapItems(unsigned int source, unsigned int destination);
	bool isItemCompatible(Item* source, Item* target);
	Item* getItemInSlot(unsigned int slot);
	Item* getSelectedItem();
	Item** getItemBar();
	unsigned int getItemBarSelectedSlot();
	void setItemBarSelectedSlot(unsigned int slot);
	unsigned int getItemBarSelectedSlotAbs();
	unsigned int getInventorySlots();

	const unsigned int TOTAL_SLOTS = 50;
	const unsigned int ITEMBAR_SLOTS = 10;
	const unsigned int MAX_ITEM_STACK = 64;
private:
	unsigned int m_itemBarSelectedSlot;
	Item** m_inventory;
	Item** m_itemBar;
};