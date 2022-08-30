#pragma once
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "Core/Services/ItemLibrary/ItemSlot.h"
#include "CraftingRecipeContract.h"
#include <string>
#include <Boost/log/trivial.hpp>

class CraftingRecipe {
public:
	CraftingRecipe(int recipeRows, int recipeColumns, Item*** recipe, Item* recipeResult);
	~CraftingRecipe();
	ItemId getRecipeResultItemId();
	CraftingRecipeContract* getCraftingRecipeContract();
	bool matchesItemPattern(unsigned int patternRows, unsigned int patternCols, ItemSlot*** itemPattern);
private:
	bool matchesSubItemPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemSlot*** itemPattern);
	bool matchEmptyPatternAroundSubPattern(unsigned int patternRows, unsigned int patternCols, unsigned int patternRowOffset, unsigned int patternColOffset, ItemSlot*** itemPattern);

	Item*** m_recipe;
	int m_recipeRows;
	int m_recipeColumns;
	Item* m_recipeResult;
	CraftingRecipeContract* m_contract;
};