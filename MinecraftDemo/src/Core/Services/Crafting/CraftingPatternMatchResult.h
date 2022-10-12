#pragma once
#include "CraftingRecipe.h"

class CraftingPatternMatchResult {
public:
	CraftingPatternMatchResult(CraftingRecipe* craftingRecipe, unsigned int matchCount);
	ItemHandle* getRecipeResult();
	ItemHandle*** getRecipe();
	unsigned int getRecipeCols();
	unsigned int getRecipeRows();
	unsigned int getMatchCount();
private:
	CraftingRecipe* m_craftingRecipe;
	unsigned int m_recipeMatchCount;
};