#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "CraftingRecipe.h"
#include "Core/Services/ItemLibrary/ItemGenerator.h"

class CraftingRecipeBuilder : public SpecializedBuilder<CraftingRecipe> {
public:
	CraftingRecipeBuilder(ItemGenerator* itemGenerator);
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
	ItemHandle*** initEmptyRecipe(unsigned int recipeRows, unsigned int recipeCols);
	ItemGenerator* m_itemGenerator;
};