#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe(int recipeRows, int recipeColumns, Item*** recipe, Item* recipeResult) :
	m_recipeRows(recipeRows),
	m_recipeColumns(recipeColumns),
	m_recipe(recipe),
	m_recipeResult(recipeResult),
	m_contract(new CraftingRecipeContract()) {
	m_contract->setRecipe(m_recipe);
	m_contract->setRecipeCols(m_recipeColumns);
	m_contract->setRecipeRows(m_recipeRows);
	m_contract->setResult(recipeResult->clone());
}

CraftingRecipe::~CraftingRecipe() {
	for (int i = 0; i < m_recipeRows; i++) {
		for (int j = 0; j < m_recipeColumns; j++) {
			if (m_recipe[i][j] != nullptr) {
				delete m_recipe[i][j];
			}
		}
		delete[] m_recipe[i];
	}
	delete[] m_recipe;
	delete m_contract;
}

ItemId CraftingRecipe::getRecipeResultItemId() {
	return m_recipeResult->getItemId();
}

bool CraftingRecipe::matchesItemPattern(unsigned int patternRows, unsigned int patternCols, ItemSlot*** itemPattern) {
	if (!(patternRows < m_recipeRows || patternCols < m_recipeColumns)) {
		m_contract->setItemPattern(itemPattern);
		m_contract->setPatternCols(patternCols);
		m_contract->setPatternRows(patternRows);
		int verticalIterations = (patternRows - m_recipeRows) + 1;
		int horizontalIterations = (patternCols - m_recipeColumns) + 1;
		for (int i = 0; i < verticalIterations; i++) {
			for (int j = 0; j < horizontalIterations; j++) {
				BOOST_LOG_TRIVIAL(info) << "offset " << i << " " << j;
				if (matchesSubItemPattern(i, j, itemPattern) && matchEmptyPatternAroundSubPattern(patternRows, patternCols, i, j, itemPattern)) {
					BOOST_LOG_TRIVIAL(info) << "PATTERN MATCH!";
					m_contract->updateResultByMultiplier();
					return true;
				}
			}
		}
	}
	return false;
}

bool CraftingRecipe::matchesSubItemPattern(unsigned int patternRowOffset, unsigned int patternColOffset, ItemSlot*** itemPattern) {
	bool oneMatch = false;
	BOOST_LOG_TRIVIAL(info) << "Computing max recipe multiplier " << m_recipeResult->getItemMaxStackCount() << " " << m_recipeResult->getItemCount();
	int maxRecipeMultiplier = m_recipeResult->getItemMaxStackCount() / m_recipeResult->getItemCount();
	for (int row = 0; row < m_recipeRows; row++) {
		for (int column = 0; column < m_recipeColumns; column++) {
			BOOST_LOG_TRIVIAL(info) << "checking " << patternRowOffset + row << " " << patternColOffset + column;
			ItemSlot* itemSlot = itemPattern[row + patternRowOffset][column + patternColOffset];
			Item* recipeItem = m_recipe[row][column];
			if ((itemSlot->isEmpty() && recipeItem != nullptr) || (!itemSlot->isEmpty() && recipeItem == nullptr)) {
				BOOST_LOG_TRIVIAL(info) << "one slot is empty the other is not";
				return false;
			}
			if (!itemSlot->isEmpty() && recipeItem != nullptr) {
				BOOST_LOG_TRIVIAL(info) << "not null " << (int)itemSlot->getItem()->getItemId() << " " << (int)recipeItem->getItemId();
				if (!(itemSlot->getItem()->getItemId() == recipeItem->getItemId() && itemSlot->getItem()->getItemCount() >= recipeItem->getItemCount())) {
					return false;
				}
				else {
					int currentMultiplier = itemSlot->getItem()->getItemCount() / recipeItem->getItemCount();
					BOOST_LOG_TRIVIAL(info) << "matched single item " << currentMultiplier << " " << glm::min(maxRecipeMultiplier, currentMultiplier);
					oneMatch = true;
					maxRecipeMultiplier = glm::min(maxRecipeMultiplier, itemSlot->getItem()->getItemCount() / recipeItem->getItemCount());
					BOOST_LOG_TRIVIAL(info) << "new value is " << maxRecipeMultiplier;
				}
			}
			else {
				BOOST_LOG_TRIVIAL(info) << "both empty";
			}
		}
	}
	BOOST_LOG_TRIVIAL(info) << "recipe multiplier is " << maxRecipeMultiplier;
	m_contract->setRecipeApplicabilityMultiplier(maxRecipeMultiplier);
	return oneMatch;
}

bool CraftingRecipe::matchEmptyPatternAroundSubPattern(unsigned int patternRows, unsigned int patternCols, unsigned int patternRowOffset, unsigned int patternColOffset, ItemSlot*** itemPattern) {
	for (int row = 0; row < patternRows; row++) {
		for (int column = 0; column < patternCols; column++) {
			if ((row < patternRowOffset || row >= (patternRowOffset + m_recipeRows)) || (column < patternColOffset || column >= (patternColOffset + m_recipeColumns))) {
				if (!itemPattern[row][column]->isEmpty()) {
					return false;
				}
			}
		}
	}
	return true;
}

CraftingRecipeContract* CraftingRecipe::getCraftingRecipeContract() {
	return m_contract;
}