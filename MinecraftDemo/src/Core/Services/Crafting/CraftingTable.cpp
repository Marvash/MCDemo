#include "CraftingTable.h"

CraftingTable::CraftingTable(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_craftingTable(new ItemHandle**[CRAFTING_TABLE_SLOTS]),
	m_craftingResult(nullptr),
	m_craftingRecipeLibrary(nullptr),
	m_matchedRecipeResult(nullptr) {
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

void CraftingTable::init(CraftingRecipeLibrary* craftingRecipeLibrary, ItemGenerator* itemGenerator) {
	m_craftingRecipeLibrary = craftingRecipeLibrary;
	m_itemGenerator = itemGenerator;
	for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
		m_craftingTable[i] = new ItemHandle * [CRAFTING_TABLE_SLOTS];
		for (int j = 0; j < CRAFTING_TABLE_SLOTS; j++) {
			m_craftingTable[i][j] = m_itemGenerator->createItemHandle(ItemId::NONE);
		}
	}
	m_craftingResult = m_itemGenerator->createItemHandle(ItemId::NONE);
}

ItemHandle* CraftingTable::getItemSlot(int row, int column) {
	ItemHandle* item = nullptr;
	if (checkRowColumnBounds(row, column)) {
		item = m_craftingTable[row][column];
	}
	else {
		std::string errorString("Specified crafting table item slot coordinates out of bounds");
		throw new GameLogicException(errorString);
	}
	return item;
}

ItemHandle* CraftingTable::getItemSlot(int index) {
	int row = index / CRAFTING_TABLE_SLOTS;
	int col = index % CRAFTING_TABLE_SLOTS;
	return getItemSlot(row, col);
}

ItemHandle* CraftingTable::getResultItemSlot() {
	return m_craftingResult;
}

bool CraftingTable::checkRowColumnBounds(int row, int column) {
	return row >= 0 && row < CRAFTING_TABLE_SLOTS&& column >= 0 && column < CRAFTING_TABLE_SLOTS;
}

void CraftingTable::matchRecipe() {
	if (m_matchedRecipeResult != nullptr) {
		delete m_matchedRecipeResult;
		m_matchedRecipeResult = nullptr;
	}
	m_matchedRecipeResult = m_craftingRecipeLibrary->matchItemPattern(CRAFTING_TABLE_SLOTS, CRAFTING_TABLE_SLOTS, m_craftingTable);
	if (m_matchedRecipeResult != nullptr) {
		ItemHandle* resultItem = m_matchedRecipeResult->getRecipeResult();
		m_itemGenerator->changeItemHandle(m_craftingResult, resultItem->getItemId(), m_matchedRecipeResult->getMatchCount() * resultItem->getItemCount());
	}
	else {
		m_craftingResult->setNull();
	}
}

void CraftingTable::applyRecipeCosts() {
	if (m_matchedRecipeResult != nullptr) {
		ItemHandle*** recipe = m_matchedRecipeResult->getRecipe();
		unsigned int recipeMatchCount = m_matchedRecipeResult->getMatchCount();
		unsigned int recipeRows = m_matchedRecipeResult->getRecipeRows();
		unsigned int recipeCols = m_matchedRecipeResult->getRecipeCols();
		int patternRowOffset = -1;
		int patternColOffset = -1;
		for (int i = 0; i < CRAFTING_TABLE_SLOTS && patternRowOffset == -1; i++) {
			for (int j = 0; j < CRAFTING_TABLE_SLOTS && patternColOffset == -1; j++) {
				ItemHandle* patternItem = m_craftingTable[i][j];
				if (!patternItem->isNullItem()) {
					patternRowOffset = i;
					patternColOffset = j;
				}
			}
		}
		for (int i = 0; i < recipeRows; i++) {
			for (int j = 0; j < recipeCols; j++) {
				int patternRowIndex = patternRowOffset + i;
				int patternColIndex = patternColOffset + j;
				ItemHandle* patternItem = m_craftingTable[patternRowIndex][patternColIndex];
				ItemHandle* recipeItem = recipe[i][j];
				if (!recipeItem->isNullItem()) {
					unsigned int toSubtract = recipeItem->getItemCount() * recipeMatchCount;
					patternItem->subtractToItemCount(toSubtract);
				}
			}
		}
	}
}

void CraftingTable::splitItemSlot(unsigned int slot) {
	if (slot < (CRAFTING_TABLE_SLOTS * CRAFTING_TABLE_SLOTS)) {
		ItemHandle* itemToSplit = getItemSlot(slot);
		if (!itemToSplit->isNullItem() && itemToSplit->getItemCount() > 1) {
			for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
				for (int j = 0; j < CRAFTING_TABLE_SLOTS; j++) {
					ItemHandle* currentItem = m_craftingTable[i][j];
					if (currentItem->isNullItem()) {
						int countHalf = (itemToSplit->getItemCount() / 2);
						m_itemGenerator->changeItemHandle(currentItem, itemToSplit->getItemId(), countHalf);
						itemToSplit->subtractToItemCount(countHalf);
						i = CRAFTING_TABLE_SLOTS;
						j = CRAFTING_TABLE_SLOTS;
					}
				}
			}
		}
	}
}

void CraftingTable::addItemInEmptyCraftingSlot(ItemId itemId, int count, unsigned int slot) {
	ItemHandle* item = getItemSlot(slot);
	if (item->isNullItem() && count > 0) {
		m_itemGenerator->changeItemHandle(item, itemId, count);
	}
}

void CraftingTable::onNotify(Event& newEvent) {

}