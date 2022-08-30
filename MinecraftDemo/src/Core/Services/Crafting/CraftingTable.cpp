#include "CraftingTable.h"

CraftingTable::CraftingTable(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_craftingTable(new ItemSlot**[CRAFTING_TABLE_SLOTS]),
	m_craftingResult(new ItemSlot()),
	m_matchingRecipe(nullptr),
	m_craftingRecipeLibrary(nullptr) {
	for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
		m_craftingTable[i] = new ItemSlot *[CRAFTING_TABLE_SLOTS];
		for (int j = 0; j < CRAFTING_TABLE_SLOTS; j++) {
			m_craftingTable[i][j] = new ItemSlot();
		}
	}
}

CraftingTable::~CraftingTable() {
	for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
		for (int j = 0; j < CRAFTING_TABLE_SLOTS; j++) {
			delete m_craftingTable[i][j];
		}
		delete[] m_craftingTable[i];
	}
	delete[] m_craftingTable;
	delete m_craftingResult;
}

void CraftingTable::init(CraftingRecipeLibrary* craftingRecipeLibrary) {
	m_craftingRecipeLibrary = craftingRecipeLibrary;
}

ItemSlot* CraftingTable::getItemSlot(int row, int column) {
	ItemSlot* itemSlot = nullptr;
	if (checkRowColumnBounds(row, column)) {
		itemSlot = m_craftingTable[row][column];
	}
	else {
		std::string errorString("Specified crafting table item slot coordinates out of bounds");
		throw new GameLogicException(errorString);
	}
	return itemSlot;
}

ItemSlot* CraftingTable::getItemSlot(int index) {
	int row = index / CRAFTING_TABLE_SLOTS;
	int col = index % CRAFTING_TABLE_SLOTS;
	return getItemSlot(row, col);
}

ItemSlot* CraftingTable::getResultItemSlot() {
	return m_craftingResult;
}

bool CraftingTable::checkRowColumnBounds(int row, int column) {
	return row >= 0 && row < CRAFTING_TABLE_SLOTS&& column >= 0 && column < CRAFTING_TABLE_SLOTS;
}

void CraftingTable::matchRecipe() {
	CraftingRecipe* matchingRecipe = m_craftingRecipeLibrary->matchItemPattern(CRAFTING_TABLE_SLOTS, CRAFTING_TABLE_SLOTS, m_craftingTable);
	if (matchingRecipe != nullptr) {
		m_matchingRecipe = matchingRecipe;
		m_craftingResult->replaceItem(m_matchingRecipe->getCraftingRecipeContract()->cloneResult());
	}
	else {
		m_craftingResult->resetItem();
		m_matchingRecipe = nullptr;
	}
}

void CraftingTable::fulfillMatchingRecipeContract() {
	if (m_matchingRecipe != nullptr) {
		m_matchingRecipe->getCraftingRecipeContract()->fulfillContract();
	}
}

void CraftingTable::onNotify(Event& newEvent) {

}