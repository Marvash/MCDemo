#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ItemLibrary/ItemGenerator.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include <glm/glm.hpp>
#include <vector>

class Inventory : public CoreService {
public:
	Inventory(CoreEventDispatcher* coreEventDispatcher);
	~Inventory();

	void init(ItemGenerator* itemGenerator);
	void onNotify(Event& newEvent) override;
	int queryAvailableSpaceForItemId(ItemId itemId);
	int queryItemCount(ItemId itemId);
	void addItem(ItemHandle* item);
	void addItem(ItemId itemId, int count);
	void removeItem(ItemId itemId, int count);
	void addItemInEmptyInventorySlot(ItemId itemId, int count, unsigned int slot);
	void splitItemInSlot(unsigned int slot);
	ItemHandle* getSelectedItem();
	ItemHandle** getItemBar();
	ItemHandle* getItemInSlot(unsigned int slot);
	unsigned int getItemBarSelectedSlot();
	void setItemBarSelectedSlot(unsigned int slot);
	unsigned int getItemBarSelectedSlotAbs();
	unsigned int getInventorySlots();

	const unsigned int TOTAL_SLOTS = 50;
	const unsigned int ITEMBAR_SLOTS = 10;
private:
	unsigned int m_itemBarSelectedSlot;
	ItemHandle** m_inventory;
	ItemHandle** m_itemBar;
	ItemGenerator* m_itemGenerator;
};