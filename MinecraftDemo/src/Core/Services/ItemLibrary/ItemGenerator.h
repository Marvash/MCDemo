#pragma once
#include "IItem.h"
#include "Item.h"
#include "ItemHandle.h"
#include "PlaceableItem.h"
#include "DefaultItem.h"
#include "ItemLibrary.h"
#include "Core/Services/CoreService.h"

class ItemGenerator : public CoreService {

	friend class Item;
	friend class ItemHandle;

public:
	ItemGenerator(CoreEventDispatcher* coreEventDispatcher);
	void init(ItemLibrary* itemLibrary);
	void onNotify(Event& newEvent) override;
	ItemHandle* createItemHandle(ItemId itemId, unsigned int count = 1);
private:
	IItem* createItem(ItemId itemId);

	IItem* createDefaultItem(ItemId itemId);
	IItem* createPlaceableItem(ItemId itemId);
	void changeItemHandle(ItemHandle* itemHandle, ItemId itemId, unsigned int count = 1);

	ItemLibrary* m_itemLibrary;
	IItem* m_nullItem;
};