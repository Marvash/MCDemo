#pragma once
#include "Core/Services/ItemLibrary/ItemSlot.h"
#include <Boost/log/trivial.hpp>

class CraftingRecipeContract {
public:
	CraftingRecipeContract();
	void fulfillContract();
	void setResult(Item* result);
	void setRecipe(Item*** recipe);
	void setRecipeRows(unsigned int recipeRows);
	void setRecipeCols(unsigned int recipeCols);
	void setPatternRows(unsigned int patternRows);
	void setPatternCols(unsigned int patternCols);
	void setItemPattern(ItemSlot*** itemPattern);
	void setRecipeApplicabilityMultiplier(int multiplier);
	void updateResultByMultiplier();
	Item* cloneResult();
private:
	void applyCostWithMultiplier(int multiplier);

	Item* m_result;
	Item* m_originalResult;
	Item*** m_recipe;
	unsigned int m_recipeRows;
	unsigned int m_recipeCols;
	unsigned int m_patternRows;
	unsigned int m_patternCols;
	ItemSlot*** m_itemPattern;
	int m_recipeApplicabilityMultiplier;
};