#include "CraftingPatternMatchResult.h"

CraftingPatternMatchResult::CraftingPatternMatchResult(CraftingRecipe* craftingRecipe, unsigned int matchCount) : 
	m_craftingRecipe(craftingRecipe),
	m_recipeMatchCount(matchCount) {

}

ItemHandle* CraftingPatternMatchResult::getRecipeResult() {
	return m_craftingRecipe->getRecipeResult();
}

ItemHandle*** CraftingPatternMatchResult::getRecipe() {
	return m_craftingRecipe->getRecipe();
}

unsigned int CraftingPatternMatchResult::getRecipeCols() {
	return m_craftingRecipe->getRecipeCols();
}

unsigned int CraftingPatternMatchResult::getRecipeRows() {
	return m_craftingRecipe->getRecipeRows();
}

unsigned int CraftingPatternMatchResult::getMatchCount() {
	return m_recipeMatchCount;
}