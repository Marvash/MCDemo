#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "CraftingRecipe.h"
#include "Core/Services/ItemLibrary/ItemLibrary.h"

class CraftingRecipeBuilder : public SpecializedBuilder<CraftingRecipe> {
public:
	CraftingRecipeBuilder(ItemLibrary* itemLibrary);
	void buildPlankRecipe();
	void buildStickRecipe();
	void buildWoodenAxeRecipe();
	void buildWoodenHoeRecipe();
	void buildWoodenPickaxeRecipe();
	void buildWoodenShovelRecipe();
	void buildWoodenSwordRecipe();
	void buildStoneAxeRecipe();
	void buildStoneHoeRecipe();
	void buildStonePickaxeRecipe();
	void buildStoneShovelRecipe();
	void buildStoneSwordRecipe();
private:
	Item*** initEmptyRecipe(unsigned int recipeRows, unsigned int recipeCols);
	ItemLibrary* m_itemLibrary;
};