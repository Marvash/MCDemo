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
	Item* recipeResult = new Item(m_itemLibrary->getItemSpecification(ItemId::STICK_ITEM), 4);
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