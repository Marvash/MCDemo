#include "BlockLibrary.h"
#include "Core/Services/CoreServiceLocator.h"

BlockLibrary::BlockLibrary(CoreServiceLocator* coreServiceLocator) : m_coreServiceLocator(coreServiceLocator) {
	generateBlockSpecifications();
	generateDroppableBlockSpecifications();
}

BlockLibrary::~BlockLibrary() {

}

BlockSharedSpec* BlockLibrary::getBlockSpecification(BlockId blockId) {
	return m_blockSpecifications[blockId];
}

DroppableBlockSharedSpec* BlockLibrary::getDroppableBlockSpecification(BlockId blockId) {
	return m_droppableBlockSpecifications[blockId];

}

void BlockLibrary::generateBlockSpecifications() {
	BlockSharedSpec* blockSpecification = nullptr;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::AIR;
	blockSpecification->m_blockItemId = ItemId::NONE;
	blockSpecification->m_displayName = "Air Block";
	blockSpecification->m_isTransparent = true;
	blockSpecification->m_isRenderable = false;
	blockSpecification->m_blockHardness = 0.0f;
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::DIRT;
	blockSpecification->m_blockItemId = ItemId::DIRT_BLOCK_ITEM;
	blockSpecification->m_displayName = "Dirt Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 1.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_SHOVEL);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_SHOVEL);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::GRASS;
	blockSpecification->m_blockItemId = ItemId::GRASS_BLOCK_ITEM;
	blockSpecification->m_displayName = "Grass Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 1.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_SHOVEL);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_SHOVEL);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::LEAVES;
	blockSpecification->m_blockItemId = ItemId::LEAVES_BLOCK_ITEM;
	blockSpecification->m_displayName = "Leaves Block";
	blockSpecification->m_isTransparent = true;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 0.5f;
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::NONE;
	blockSpecification->m_blockItemId = ItemId::NONE;
	blockSpecification->m_displayName = "None";
	blockSpecification->m_isTransparent = true;
	blockSpecification->m_isRenderable = false;
	blockSpecification->m_blockHardness = 0.0f;
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::OAK_LOG;
	blockSpecification->m_blockItemId = ItemId::OAK_LOG_BLOCK_ITEM;
	blockSpecification->m_displayName = "Oak Log Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 2.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_AXE);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_AXE);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::PLANK;
	blockSpecification->m_blockItemId = ItemId::PLANK_BLOCK_ITEM;
	blockSpecification->m_displayName = "Plank Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 2.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_AXE);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_AXE);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::SAND;
	blockSpecification->m_blockItemId = ItemId::SAND_BLOCK_ITEM;
	blockSpecification->m_displayName = "Sand Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 1.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_SHOVEL);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_SHOVEL);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::SNOWY_GRASS;
	blockSpecification->m_blockItemId = ItemId::SNOWY_GRASS_BLOCK_ITEM;
	blockSpecification->m_displayName = "Snowy Grass Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 1.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_SHOVEL);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_SHOVEL);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::STONE;
	blockSpecification->m_blockItemId = ItemId::STONE_BLOCK_ITEM;
	blockSpecification->m_displayName = "Stone Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 20.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_PICKAXE);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_PICKAXE);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
	blockSpecification = new BlockSharedSpec();
	blockSpecification->m_blockId = BlockId::COBBLESTONE;
	blockSpecification->m_blockItemId = ItemId::COBBLESTONE_BLOCK_ITEM;
	blockSpecification->m_displayName = "Cobblestone Block";
	blockSpecification->m_isTransparent = false;
	blockSpecification->m_isRenderable = true;
	blockSpecification->m_blockHardness = 20.0f;
	blockSpecification->m_itemWeaknesses.push_back(ItemId::WOODEN_PICKAXE);
	blockSpecification->m_itemWeaknesses.push_back(ItemId::STONE_PICKAXE);
	m_blockSpecifications[blockSpecification->m_blockId] = blockSpecification;
}

void BlockLibrary::generateDroppableBlockSpecifications() {
	DroppableBlockSharedSpec* droppableBlockSpecification = nullptr;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::DIRT_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::DIRT] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::DIRT_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::GRASS] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::DIRT_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::SNOWY_GRASS] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::OAK_LOG_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::OAK_LOG] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::PLANK_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::PLANK] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::SAND_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::SAND] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::LEAVES_BLOCK_ITEM;
	m_droppableBlockSpecifications[BlockId::LEAVES] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::COBBLESTONE_BLOCK_ITEM;
	droppableBlockSpecification->m_exclusiveItemDropList.push_back(ItemId::WOODEN_PICKAXE);
	droppableBlockSpecification->m_exclusiveItemDropList.push_back(ItemId::STONE_PICKAXE);
	m_droppableBlockSpecifications[BlockId::STONE] = droppableBlockSpecification;
	droppableBlockSpecification = new DroppableBlockSharedSpec();
	droppableBlockSpecification->m_coreServiceLocator = m_coreServiceLocator;
	droppableBlockSpecification->m_droppedCount = 1;
	droppableBlockSpecification->m_droppedItem = ItemId::COBBLESTONE_BLOCK_ITEM;
	droppableBlockSpecification->m_exclusiveItemDropList.push_back(ItemId::WOODEN_PICKAXE);
	droppableBlockSpecification->m_exclusiveItemDropList.push_back(ItemId::STONE_PICKAXE);
	m_droppableBlockSpecifications[BlockId::COBBLESTONE] = droppableBlockSpecification;
}