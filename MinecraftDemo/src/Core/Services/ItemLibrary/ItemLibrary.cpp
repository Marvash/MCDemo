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
	m_itemSpecifications[ItemId::STICK] = new DefaultItemSpecification(ItemId::STICK, m_iconLibrary->getItemIcon(ItemId::STICK));
	m_itemSpecifications[ItemId::WOODEN_AXE] = new ToolItemSpecification(ItemId::WOODEN_AXE, m_iconLibrary->getItemIcon(ItemId::WOODEN_AXE));
	m_itemSpecifications[ItemId::WOODEN_HOE] = new ToolItemSpecification(ItemId::WOODEN_HOE, m_iconLibrary->getItemIcon(ItemId::WOODEN_HOE));
	m_itemSpecifications[ItemId::WOODEN_PICKAXE] = new ToolItemSpecification(ItemId::WOODEN_PICKAXE, m_iconLibrary->getItemIcon(ItemId::WOODEN_PICKAXE));
	m_itemSpecifications[ItemId::WOODEN_SHOVEL] = new ToolItemSpecification(ItemId::WOODEN_SHOVEL, m_iconLibrary->getItemIcon(ItemId::WOODEN_SHOVEL));
	m_itemSpecifications[ItemId::WOODEN_SWORD] = new ToolItemSpecification(ItemId::WOODEN_SWORD, m_iconLibrary->getItemIcon(ItemId::WOODEN_SWORD));
	m_itemSpecifications[ItemId::STONE_AXE] = new ToolItemSpecification(ItemId::STONE_AXE, m_iconLibrary->getItemIcon(ItemId::STONE_AXE));
	m_itemSpecifications[ItemId::STONE_HOE] = new ToolItemSpecification(ItemId::STONE_HOE, m_iconLibrary->getItemIcon(ItemId::STONE_HOE));
	m_itemSpecifications[ItemId::STONE_PICKAXE] = new ToolItemSpecification(ItemId::STONE_PICKAXE, m_iconLibrary->getItemIcon(ItemId::STONE_PICKAXE));
	m_itemSpecifications[ItemId::STONE_SHOVEL] = new ToolItemSpecification(ItemId::STONE_SHOVEL, m_iconLibrary->getItemIcon(ItemId::STONE_SHOVEL));
	m_itemSpecifications[ItemId::STONE_SWORD] = new ToolItemSpecification(ItemId::STONE_SWORD, m_iconLibrary->getItemIcon(ItemId::STONE_SWORD));
	m_itemSpecifications[ItemId::LAST_ITEM] = new NullItemSpecification(ItemId::LAST_ITEM, nullptr);
}

ItemSpecification* ItemLibrary::getItemSpecification(ItemId itemId) {
	return m_itemSpecifications[itemId];
}

void ItemLibrary::onNotify(Event& newEvent) {

}