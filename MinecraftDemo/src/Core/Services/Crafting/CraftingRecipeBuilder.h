#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "CraftingRecipe.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"

class CraftingRecipeBuilder : public SpecializedBuilder<CraftingRecipe> {
public:
	CraftingRecipeBuilder(ItemLibrary* itemLibrary);
	void buildPlankRecipe();
private:
	Item*** initEmptyRecipe(unsigned int recipeRows, unsigned int recipeCols);
	ItemLibrary* m_itemLibrary;
};