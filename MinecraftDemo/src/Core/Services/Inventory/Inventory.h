#pragma once
#include "Core/Cube/Cube.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"
#include "Core/Services/ItemLibrary/Item.h"
#include <glm/glm.hpp>
#include <vector>

class Inventory : public CoreService {
public:
	Inventory(CoreEventDispatcher* coreEventDispatcher);
	~Inventory();

	void init(ItemLibrary* itemLibrary);
	void onNotify(Event& newEvent) override;
	int queryAvailableSpaceForItemId(ItemId itemId);
	int queryItemCount(ItemId itemId);
	void addItem(ItemId itemId, int count);
	void removeItem(ItemId itemId, int count);
	void addItemInInventorySlot(ItemId itemId, int count, unsigned int slot);
	void decreaseItemCountInSlot(int count, unsigned int slot);
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
private:
	unsigned int m_itemBarSelectedSlot;
	Item** m_inventory;
	Item** m_itemBar;
	ItemLibrary* m_itemLibrary;
};