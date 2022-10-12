#include "CraftingPatternMatcher.h"

CraftingPatternMatcher::CraftingPatternMatcher(unsigned int patternRows, unsigned int patternCols) :
	m_patternCols(patternCols),
	m_patternRows(patternRows) {

}

bool CraftingPatternMatcher::matchRecipe(ItemHandle*** itemPattern, CraftingRecipe* recipe) {
	m_recipe = recipe;
	if (!(m_patternRows < m_recipe->getRecipeRows() || m_patternCols < m_recipe->getRecipeCols())) {
		int verticalIterations = (m_patternRows - m_recipe->getRecipeRows()) + 1;
		int horizontalIterations = (m_patternCols - m_recipe->getRecipeCols()) + 1;
		for (int i = 0; i < verticalIterations; i++) {
			for (int j = 0; j < horizontalIterations; j++) {
				if (matchesSubItemPattern(i, j, itemPattern) && matchEmptyPatternAroundSubPattern(i, j, itemPattern)) {
					return true;
				}
			}
		}
	}
	return false;
}

unsigned int CraftingPatternMatcher::getRecipeMatchCount() {
	return m_recipeMatchCount;
}

bool CraftingPatternMatcher::matchesSubItemPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemHandle*** itemPattern) {
	ItemHandle* recipeResult = m_recipe->getRecipeResult();
	ItemHandle*** recipePattern = m_recipe->getRecipe();
	bool oneMatch = false;
	int maxRecipeMultiplier = recipeResult->getItemMaxStackCount() / recipeResult->getItemCount();
	for (int row = 0; row < m_recipe->getRecipeRows(); row++) {
		for (int column = 0; column < m_recipe->getRecipeCols(); column++) {
			ItemHandle* item = itemPattern[row + patternRowOffset][column + patternColOffset];
			ItemHandle* recipeItem = recipePattern[row][column];
			if (item->isNullItem() != recipeItem->isNullItem()) {
				return false;
			}
			if (!item->isNullItem()) {
				if (!(item->getItemId() == recipeItem->getItemId() && item->getItemCount() >= recipeItem->getItemCount())) {
					return false;
				}
				else {
					int currentMultiplier = item->getItemCount() / recipeItem->getItemCount();
					oneMatch = true;
					maxRecipeMultiplier = glm::min(maxRecipeMultiplier, item->getItemCount() / recipeItem->getItemCount());
				}
			}
		}
	}
	m_recipeMatchCount = maxRecipeMultiplier;
	return oneMatch;
}

bool CraftingPatternMatcher::matchEmptyPatternAroundSubPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemHandle*** itemPattern) {
	for (int row = 0; row < m_patternRows; row++) {
		for (int column = 0; column < m_patternCols; column++) {
			if ((row < patternRowOffset || row >= (patternRowOffset + m_recipe->getRecipeRows())) || (column < patternColOffset || column >= (patternColOffset + m_recipe->getRecipeCols()))) {
				if (!itemPattern[row][column]->isNullItem()) {
					return false;
				}
			}
		}
	}
	return true;
}