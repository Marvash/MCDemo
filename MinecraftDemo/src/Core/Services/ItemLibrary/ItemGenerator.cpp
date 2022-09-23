#include "ItemGenerator.h"

ItemGenerator::ItemGenerator(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_itemLibrary(nullptr),
	m_nullItem(nullptr) {
}

void ItemGenerator::init(ItemLibrary* itemLibrary) {
	m_itemLibrary = itemLibrary;
	m_nullItem = createDefaultItem(ItemId::NONE);
}

void ItemGenerator::onNotify(Event& newEvent) {

}

ItemHandle* ItemGenerator::createItem(ItemId itemId, unsigned int count) {
	IItem* item = nullptr;
	switch (itemId) {
		case ItemId::STICK:
		case ItemId::WOODEN_AXE:
		case ItemId::WOODEN_HOE:
		case ItemId::WOODEN_PICKAXE:
		case ItemId::WOODEN_SHOVEL:
		case ItemId::WOODEN_SWORD:
		case ItemId::STONE_AXE:
		case ItemId::STONE_HOE:
		case ItemId::STONE_PICKAXE:
		case ItemId::STONE_SHOVEL:
		case ItemId::STONE_SWORD:
			item = createDefaultItem(itemId);
			break;
		case ItemId::DIRT_BLOCK_ITEM:
		case ItemId::GRASS_BLOCK_ITEM:
		case ItemId::SNOWY_GRASS_BLOCK_ITEM:
		case ItemId::SAND_BLOCK_ITEM:
		case ItemId::STONE_BLOCK_ITEM:
		case ItemId::OAK_LOG_BLOCK_ITEM:
		case ItemId::LEAVES_BLOCK_ITEM:
		case ItemId::PLANK_BLOCK_ITEM:
			item = createPlaceableItem(itemId);
			break;
	}
	ItemHandle* itemHandle = new ItemHandle();
	itemHandle->setNullItemInstance(m_nullItem);
	if (item != nullptr) {
		itemHandle->setWrappedItemInstance(item, count);
	}
	return itemHandle;
}

void ItemGenerator::changeItemHandle(ItemHandle* itemHandle, ItemId itemId, unsigned int count) {
	IItem* item = nullptr;
	switch (itemId) {
	case ItemId::STICK:
	case ItemId::WOODEN_AXE:
	case ItemId::WOODEN_HOE:
	case ItemId::WOODEN_PICKAXE:
	case ItemId::WOODEN_SHOVEL:
	case ItemId::WOODEN_SWORD:
	case ItemId::STONE_AXE:
	case ItemId::STONE_HOE:
	case ItemId::STONE_PICKAXE:
	case ItemId::STONE_SHOVEL:
	case ItemId::STONE_SWORD:
		item = createDefaultItem(itemId);
		break;
	case ItemId::DIRT_BLOCK_ITEM:
	case ItemId::GRASS_BLOCK_ITEM:
	case ItemId::SNOWY_GRASS_BLOCK_ITEM:
	case ItemId::SAND_BLOCK_ITEM:
	case ItemId::STONE_BLOCK_ITEM:
	case ItemId::OAK_LOG_BLOCK_ITEM:
	case ItemId::LEAVES_BLOCK_ITEM:
	case ItemId::PLANK_BLOCK_ITEM:
		item = createPlaceableItem(itemId);
		break;
	}
	itemHandle->setNull();
	if (item != nullptr) {
		itemHandle->setWrappedItemInstance(item, count);
	}
	
}

IItem* ItemGenerator::createDefaultItem(ItemId itemId) {
	Item* item = new Item();
	item->m_itemSharedSpec = m_itemLibrary->getItemSpecification(itemId);
	DefaultItem* defaultItem = new DefaultItem(item);
	return defaultItem;
}

IItem* ItemGenerator::createPlaceableItem(ItemId itemId) {
	IItem* item = createDefaultItem(itemId);
	PlaceableItem* placeableItem = new PlaceableItem(item);
	placeableItem->m_placeableItemSharedSpec = m_itemLibrary->getPlaceableItemSpecification(itemId);
	return placeableItem;
}