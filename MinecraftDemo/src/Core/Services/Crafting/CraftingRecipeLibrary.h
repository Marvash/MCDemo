#pragma once
#include "CraftingRecipe.h"
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include "Core/Services/ItemLibrary/ItemGenerator.h"
#include "CraftingPatternMatchResult.h"
#include "CraftingRecipeBuilder.h"
#include "CraftingPatternMatcher.h"
#include <map>

class CraftingRecipeLibrary {
public:
	CraftingRecipeLibrary();
	void init(ItemGenerator* itemGenerator);
	CraftingPatternMatchResult* matchItemPattern(unsigned int patternRows, unsigned int patternCols, ItemHandle*** itemPattern);
private:
	void populateCraftingRecipeLibrary();
	std::vector<CraftingRecipe*> m_craftingRecipes;
	ItemGenerator* m_itemGenerator;
};