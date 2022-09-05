#include "CraftingRecipeBuilder.h"

CraftingRecipeBuilder::CraftingRecipeBuilder(ItemLibrary* itemLibrary) : m_itemLibrary(itemLibrary) {

}

void CraftingRecipeBuilder::buildPlankRecipe() {
	unsigned int recipeRows = 1;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::OAK_LOG_BLOCK_ITEM));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM), 4);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStickRecipe() {
	unsigned int recipeRows = 2;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK), 4);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenAxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::WOODEN_AXE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenHoeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][0] = nullptr;
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::WOODEN_HOE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenPickaxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 3;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[0][2] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][0] = nullptr;
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][2] = nullptr;
	recipe[2][0] = nullptr;
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][2] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::WOODEN_PICKAXE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenShovelRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::WOODEN_SHOVEL), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildWoodenSwordRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::PLANK_BLOCK_ITEM));
	recipe[2][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::WOODEN_SWORD), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneAxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_AXE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneHoeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 2;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][0] = nullptr;
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_HOE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStonePickaxeRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 3;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[0][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[0][2] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[1][0] = nullptr;
	recipe[1][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[1][2] = nullptr;
	recipe[2][0] = nullptr;
	recipe[2][1] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][2] = nullptr;
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_PICKAXE), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneShovelRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	recipe[2][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_SHOVEL), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}

void CraftingRecipeBuilder::buildStoneSwordRecipe() {
	unsigned int recipeRows = 3;
	unsigned int recipeCols = 1;
	Item*** recipe = initEmptyRecipe(recipeRows, recipeCols);
	recipe[0][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[1][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_BLOCK_ITEM));
	recipe[2][0] = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK));
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STONE_SWORD), 1);
	CraftingRecipe* craftingRecipe = new CraftingRecipe(recipeRows, recipeCols, recipe, recipeResult);
	m_result = craftingRecipe;
}


Item*** CraftingRecipeBuilder::initEmptyRecipe(unsigned int recipeRows, unsigned int recipeCols) {
	Item*** recipe = new Item * *[recipeRows];
	for (int i = 0; i < recipeRows; i++) {
		recipe[i] = new Item * [recipeCols];
		for (int j = 0; j < recipeCols; j++) {
			recipe[i][j] = nullptr;
		}
	}
	return recipe;
}