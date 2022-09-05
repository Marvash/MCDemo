#include "CraftingRecipeLibrary.h"

CraftingRecipeLibrary::CraftingRecipeLibrary() : m_itemLibrary(nullptr) {

}

void CraftingRecipeLibrary::init(ItemLibrary* itemLibrary) {
	m_itemLibrary = itemLibrary;
	populateCraftingRecipeLibrary();
}

void CraftingRecipeLibrary::populateCraftingRecipeLibrary() {
	CraftingRecipeBuilder craftingRecipeBuilder(m_itemLibrary);
	craftingRecipeBuilder.buildPlankRecipe();
	CraftingRecipe* recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStickRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
}

CraftingRecipe* CraftingRecipeLibrary::matchItemPattern(unsigned int patternRows, unsigned int patternCols, ItemSlot*** craftingTable) {
	CraftingRecipe* matchedRecipe = nullptr;
	for (CraftingRecipe* recipe : m_craftingRecipes) {
		if (recipe->matchesItemPattern(patternRows, patternCols, craftingTable)) {
			matchedRecipe = recipe;
		}
	}
	return matchedRecipe;
}