#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe(int recipeRows, int recipeColumns, ItemHandle*** recipe, ItemHandle* recipeResult) :
	m_recipeRows(recipeRows),
	m_recipeColumns(recipeColumns),
	m_recipe(recipe),
	m_recipeResult(recipeResult) {
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
}

int CraftingRecipe::getRecipeCols() {
	return m_recipeColumns;
}

int CraftingRecipe::getRecipeRows() {
	return m_recipeRows;
}

ItemHandle* CraftingRecipe::getRecipeResult() {
	return m_recipeResult;
}

ItemHandle*** CraftingRecipe::getRecipe() {
	return m_recipe;
}