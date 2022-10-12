#pragma once
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include "CraftingRecipe.h"
#include <glm/common.hpp>

class CraftingPatternMatcher {
public:
	CraftingPatternMatcher(unsigned int patternRows, unsigned int patternCols);
	unsigned int getRecipeMatchCount();
	bool matchRecipe(ItemHandle*** itemPattern, CraftingRecipe* recipe);
private:
	bool matchesSubItemPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemHandle*** itemPattern);
	bool matchEmptyPatternAroundSubPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemHandle*** itemPattern);

	unsigned int m_patternCols;
	unsigned int m_patternRows;
	unsigned int m_recipeMatchCount;
	CraftingRecipe* m_recipe;
};