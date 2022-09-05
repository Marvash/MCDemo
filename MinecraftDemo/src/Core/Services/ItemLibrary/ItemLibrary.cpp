#include "ItemLibrary.h"

ItemLibrary::ItemLibrary(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_iconLibrary(nullptr) {

}

ItemLibrary::~ItemLibrary() {
	if (m_iconLibrary != nullptr) {
		delete m_iconLibrary;
	}
}

void ItemLibrary::init(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas) {
	m_iconLibrary = new IconLibrary(renderer, biomeLibrary, atlas);
	generateItemSpecifications();
}

void ItemLibrary::generateItemSpecifications() {
	m_itemSpecifications[ItemId::NONE] = new NullItemSpecification(ItemId::NONE, nullptr);
	m_itemSpecifications[ItemId::DIRT_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::DIRT_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::DIRT_BLOCK_ITEM), CubeId::DIRT_BLOCK);
	m_itemSpecifications[ItemId::GRASS_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::GRASS_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::GRASS_BLOCK_ITEM), CubeId::GRASS_BLOCK);
	m_itemSpecifications[ItemId::STONE_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::STONE_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::STONE_BLOCK_ITEM), CubeId::STONE_BLOCK);
	m_itemSpecifications[ItemId::SAND_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::SAND_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::SAND_BLOCK_ITEM), CubeId::SAND_BLOCK);
	m_itemSpecifications[ItemId::SNOWY_GRASS_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::SNOWY_GRASS_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::SNOWY_GRASS_BLOCK_ITEM), CubeId::SNOWY_GRASS_BLOCK);
	m_itemSpecifications[ItemId::OAK_LOG_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::OAK_LOG_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::OAK_LOG_BLOCK_ITEM), CubeId::OAK_LOG_BLOCK);
	m_itemSpecifications[ItemId::LEAVES_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::LEAVES_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::LEAVES_BLOCK_ITEM), CubeId::LEAVES_BLOCK);
	m_itemSpecifications[ItemId::PLANK_BLOCK_ITEM] = new PlaceableItemSpecification(ItemId::PLANK_BLOCK_ITEM, m_iconLibrary->getItemIcon(ItemId::PLANK_BLOCK_ITEM), CubeId::PLANK_BLOCK);
	m_itemSpecifications[ItemId::STICK_ITEM] = new DefaultItemSpecification(ItemId::STICK_ITEM, m_iconLibrary->getItemIcon(ItemId::STICK_ITEM));
	m_itemSpecifications[ItemId::LAST_ITEM] = new NullItemSpecification(ItemId::LAST_ITEM, nullptr);
}

ItemSpecification* ItemLibrary::getItemSpecification(ItemId itemId) {
	return m_itemSpecifications[itemId];
}

void ItemLibrary::onNotify(Event& newEvent) {

}