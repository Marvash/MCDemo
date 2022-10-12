#include "ItemLibrary.h"

ItemLibrary::ItemLibrary() : 
	m_iconLibrary(nullptr) {

}

ItemLibrary::~ItemLibrary() {
	if (m_iconLibrary != nullptr) {
		delete m_iconLibrary;
	}
}

void ItemLibrary::init(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas, BlockLibrary* blockLibrary) {
	m_iconLibrary = new IconLibrary(renderer, biomeLibrary, atlas, blockLibrary);
	generateItemSpecifications();
	generatePlaceableItemSpecifications();
}

void ItemLibrary::generateItemSpecifications() {
	ItemSharedSpec* itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::NONE;
	itemSharedSpec->m_itemIcon = nullptr;
	itemSharedSpec->m_itemMaxStackCount = 0;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::NONE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::DIRT_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::DIRT_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::DIRT_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::GRASS_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::GRASS_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::GRASS_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::STONE_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::SAND_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::SAND_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::SAND_BLOCK_ITEM] = itemSharedSpec; itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::SNOWY_GRASS_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::SNOWY_GRASS_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::SNOWY_GRASS_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::OAK_LOG_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::OAK_LOG_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::OAK_LOG_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::LEAVES_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::LEAVES_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::LEAVES_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::PLANK_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::PLANK_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::PLANK_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::COBBLESTONE_BLOCK_ITEM;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::COBBLESTONE_BLOCK_ITEM);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::COBBLESTONE_BLOCK_ITEM] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STICK;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STICK);
	itemSharedSpec->m_itemMaxStackCount = 64;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::STICK] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::WOODEN_AXE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::WOODEN_AXE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.7f;
	m_itemSpecifications[ItemId::WOODEN_AXE] = itemSharedSpec; itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::WOODEN_HOE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::WOODEN_HOE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::WOODEN_HOE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::WOODEN_PICKAXE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::WOODEN_PICKAXE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.15f;
	m_itemSpecifications[ItemId::WOODEN_PICKAXE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::WOODEN_SHOVEL;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::WOODEN_SHOVEL);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.7f;
	m_itemSpecifications[ItemId::WOODEN_SHOVEL] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::WOODEN_SWORD;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::WOODEN_SWORD);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::WOODEN_SWORD] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_AXE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_AXE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.5f;
	m_itemSpecifications[ItemId::STONE_AXE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_HOE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_HOE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::STONE_HOE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_PICKAXE;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_PICKAXE);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.08f;
	m_itemSpecifications[ItemId::STONE_PICKAXE] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_SHOVEL;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_SHOVEL);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 0.3f;
	m_itemSpecifications[ItemId::STONE_SHOVEL] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::STONE_SWORD;
	itemSharedSpec->m_itemIcon = m_iconLibrary->getItemIcon(ItemId::STONE_SWORD);
	itemSharedSpec->m_itemMaxStackCount = 1;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::STONE_SWORD] = itemSharedSpec;
	itemSharedSpec = new ItemSharedSpec();
	itemSharedSpec->m_itemId = ItemId::LAST_ITEM;
	itemSharedSpec->m_itemIcon = nullptr;
	itemSharedSpec->m_itemMaxStackCount = 0;
	itemSharedSpec->m_itemBreakScalingFactor = 1.0f;
	m_itemSpecifications[ItemId::LAST_ITEM] = itemSharedSpec;
}

void ItemLibrary::generatePlaceableItemSpecifications() {
	PlaceableItemSharedSpec* placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::DIRT;
	m_placeableItemSpecifications[ItemId::DIRT_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::GRASS;
	m_placeableItemSpecifications[ItemId::GRASS_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::STONE;
	m_placeableItemSpecifications[ItemId::STONE_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::SAND;
	m_placeableItemSpecifications[ItemId::SAND_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::SNOWY_GRASS;
	m_placeableItemSpecifications[ItemId::SNOWY_GRASS_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::OAK_LOG;
	m_placeableItemSpecifications[ItemId::OAK_LOG_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::LEAVES;
	m_placeableItemSpecifications[ItemId::LEAVES_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::PLANK;
	m_placeableItemSpecifications[ItemId::PLANK_BLOCK_ITEM] = placeableItemSharedSpec;
	placeableItemSharedSpec = new PlaceableItemSharedSpec();
	placeableItemSharedSpec->m_itemPlaceInterval = 0.3f;
	placeableItemSharedSpec->m_blockId = BlockId::COBBLESTONE;
	m_placeableItemSpecifications[ItemId::COBBLESTONE_BLOCK_ITEM] = placeableItemSharedSpec;
}

ItemSharedSpec* ItemLibrary::getItemSpecification(ItemId itemId) {
	return m_itemSpecifications[itemId];
}

PlaceableItemSharedSpec* ItemLibrary::getPlaceableItemSpecification(ItemId itemId) {
	return m_placeableItemSpecifications[itemId];
}