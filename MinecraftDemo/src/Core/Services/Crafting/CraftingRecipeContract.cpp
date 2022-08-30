#include "CraftingRecipeContract.h"

CraftingRecipeContract::CraftingRecipeContract() :
	m_result(nullptr),
	m_recipe(nullptr),
	m_recipeRows(0),
	m_recipeCols(0),
	m_patternRows(0),
	m_patternCols(0),
	m_itemPattern(nullptr),
	m_recipeApplicabilityMultiplier(0) {
}

void CraftingRecipeContract::setResult(Item* result) {
	m_result = result;
	m_originalResult = m_result->clone();
}

void CraftingRecipeContract::setRecipe(Item*** recipe) {
	m_recipe = recipe;
}

void CraftingRecipeContract::setRecipeRows(unsigned int recipeRows) {
	m_recipeRows = recipeRows;
}

void CraftingRecipeContract::setRecipeCols(unsigned int recipeCols) {
	m_recipeCols = recipeCols;
}

void CraftingRecipeContract::setPatternRows(unsigned int patternRows) {
	m_patternRows = patternRows;
}

void CraftingRecipeContract::setPatternCols(unsigned int patternCols) {
	m_patternCols = patternCols;
}

void CraftingRecipeContract::setItemPattern(ItemSlot*** itemPattern) {
	m_itemPattern = itemPattern;
}

void CraftingRecipeContract::setRecipeApplicabilityMultiplier(int multiplier) {
	m_recipeApplicabilityMultiplier = multiplier;
}

void CraftingRecipeContract::updateResultByMultiplier() {
	m_result->setItemCount(m_originalResult->getItemCount() * m_recipeApplicabilityMultiplier);
}

void CraftingRecipeContract::fulfillContract() {
	applyCostWithMultiplier(m_recipeApplicabilityMultiplier);
}

Item* CraftingRecipeContract::cloneResult() {
	return m_result->clone();
}

void CraftingRecipeContract::applyCostWithMultiplier(int multiplier) {
	int rowOffset = -1;
	int columnOffset = -1;
	for (int row = 0; row < m_patternRows; row++) {
		for (int column = 0; column < m_patternCols; column++) {
			if (rowOffset == -1 && columnOffset == -1 && !m_itemPattern[row][column]->isEmpty()) {
				rowOffset = row;
				columnOffset = column;
			}
		}
	}
	for (int row = 0; row < m_recipeRows; row++) {
		for (int column = 0; column < m_recipeCols; column++) {
			ItemSlot* itemSlot = m_itemPattern[row + rowOffset][column + columnOffset];
			Item* recipeItem = m_recipe[row][column];
			if (!itemSlot->isEmpty() && recipeItem != nullptr) {
				itemSlot->decreaseItemCountBy(recipeItem->getItemCount() * multiplier);
			}
		}
	}
}