#include "CraftingRecipeLibrary.h"

CraftingRecipeLibrary::CraftingRecipeLibrary() : m_itemGenerator(nullptr) {

}

void CraftingRecipeLibrary::init(ItemGenerator* itemGenerator) {
	m_itemGenerator = itemGenerator;
	populateCraftingRecipeLibrary();
}

void CraftingRecipeLibrary::populateCraftingRecipeLibrary() {
	CraftingRecipeBuilder craftingRecipeBuilder(m_itemGenerator);
	craftingRecipeBuilder.buildPlankRecipe();
	CraftingRecipe* recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStickRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildWoodenAxeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildWoodenHoeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildWoodenPickaxeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildWoodenShovelRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildWoodenSwordRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStoneAxeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStoneHoeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStonePickaxeRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStoneShovelRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
	craftingRecipeBuilder.buildStoneSwordRecipe();
	recipe = craftingRecipeBuilder.getResult();
	m_craftingRecipes.push_back(recipe);
}

CraftingPatternMatchResult* CraftingRecipeLibrary::matchItemPattern(unsigned int patternRows, unsigned int patternCols, ItemHandle*** craftingTable) {
	CraftingPatternMatcher matcher(patternRows, patternCols);
	CraftingPatternMatchResult* recipeResult = nullptr;
	for (CraftingRecipe* recipe : m_craftingRecipes) {
		if (matcher.matchRecipe(craftingTable, recipe)) {
			recipeResult = new CraftingPatternMatchResult(recipe, matcher.getRecipeMatchCount());
		}
	}
	return recipeResult;
}