#include "CraftingRecipeBuilder.h"

CraftingRecipeBuilder::CraftingRecipeBuilder(ItemGenerator* itemGenerator) : m_itemGenerator(itemGenerator) {

}

void CraftingRecipeBuilder::buildPlankRecipe() {
	unsigned int recipeRows = 1;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::OAK_LOG_BLOCK_ITEM);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM, 4);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStickRecipe() {
	unsigned int recipeRows = 2;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STICK, 4);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenAxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::WOODEN_AXE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenHoeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::WOODEN_HOE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenPickaxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 3;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[0][2] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][2] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][2] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::WOODEN_PICKAXE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenShovelRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::STICK);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::WOODEN_SHOVEL);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenSwordRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::PLANK_BLOCK_ITEM);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::STICK);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::WOODEN_SWORD);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneAxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STONE_AXE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneHoeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STONE_HOE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStonePickaxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 3;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[0][1] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[0][2] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[1][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[1][2] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::NONE);
	recipe[2][1] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][2] = m_itemGenerator->createItem(ItemId::NONE);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STONE_PICKAXE);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneShovelRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::STICK);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::STICK);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STONE_SHOVEL);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneSwordRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	ItemHandle*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[1][0] = m_itemGenerator->createItem(ItemId::STONE_BLOCK_ITEM);
	recipe[2][0] = m_itemGenerator->createItem(ItemId::STICK);
	ItemHandle* recipeResult = m_itemGenerator->createItem(ItemId::STONE_SWORD);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}


ItemHandle*** CraftingRecipeBuilder::initEmptyRecipe(unsigned int recipeRows, unsigned int recipeCols) {
	ItemHandle*** recipe = new ItemHandle * *[recipeRows];
	for (int i = 0; i < recipeRows; i++) {
		recipe[i] = new ItemHandle * [recipeCols];
		for (int j = 0; j < recipeCols; j++) {
			recipe[i][j] = nullptr;
		}
	}
	return recipe;
}