#pragma once
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include <string>
#include <Boost/log/trivial.hpp>

class CraftingRecipe {
public:
	CraftingRecipe(int recipeRows, int recipeColumns, ItemHandle*** recipe, ItemHandle* recipeResult);
	~CraftingRecipe();
	int getRecipeCols();
	int getRecipeRows();
	ItemHandle* getRecipeResult();
	ItemHandle*** getRecipe();
private:

	ItemHandle*** m_recipe;
	int m_recipeRows;
	int m_recipeColumns;
	ItemHandle* m_recipeResult;
};