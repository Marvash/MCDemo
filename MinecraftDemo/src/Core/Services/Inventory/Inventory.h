#pragma once
#include "Core/Cube/Cube.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"
#include "Core/Services/ItemLibrary/ItemSlot.h"
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
	void splitItemSlot(unsigned int slot);
	Item* takeItemFromInventorySlot(unsigned int slot);
	void moveExistingItemInSlot(unsigned int slot, Item* item);
	Item* getSelectedItem();
	ItemSlot** getItemBar();
	ItemSlot* getItemSlot(unsigned int slot);
	unsigned int getItemBarSelectedSlot();
	void setItemBarSelectedSlot(unsigned int slot);
	unsigned int getItemBarSelectedSlotAbs();
	unsigned int getInventorySlots();

	const unsigned int TOTAL_SLOTS = 50;
	const unsigned int ITEMBAR_SLOTS = 10;
private:
	unsigned int m_itemBarSelectedSlot;
	ItemSlot** m_inventory;
	ItemSlot** m_itemBar;
	ItemLibrary* m_itemLibrary;
};