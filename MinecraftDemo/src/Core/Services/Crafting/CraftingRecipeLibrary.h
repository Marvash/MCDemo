#pragma once
#include "CraftingRecipe.h"
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"
#include "CraftingRecipeBuilder.h"
#include <map>

class CraftingRecipeLibrary {
public:
	CraftingRecipeLibrary();
	void init(ItemLibrary* itemLibrary);
	CraftingRecipe* matchItemPattern(unsigned int patternRows, unsigned int patternCols, ItemSlot*** itemPattern);
private:
	void populateCraftingRecipeLibrary();
	std::vector<CraftingRecipe*> m_craftingRecipes;
	ItemLibrary* m_itemLibrary;
};