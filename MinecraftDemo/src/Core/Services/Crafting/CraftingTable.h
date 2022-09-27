#pragma once
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include "CraftingRecipeLibrary.h"
#include "CraftingPatternMatchResult.h"
#include "Core/Exceptions/GameLogicException.h"
#include "Core/Services/ItemLibrary/ItemGenerator.h"

class CraftingTable : public CoreService {
public:
	CraftingTable(CoreEventDispatcher* coreEventDispatcher);
	~CraftingTable();
	void init(CraftingRecipeLibrary* craftingRecipeLibrary, ItemGenerator* itemGenerator);
	void onNotify(Event& newEvent) override;
	ItemHandle* getItemSlot(int row, int column);
	ItemHandle* getItemSlot(int index);
	ItemHandle* getResultItemSlot();
	void addItemInEmptyCraftingSlot(ItemId itemId, int count, unsigned int slot);
	void splitItemSlot(unsigned int slot);
	void matchRecipe();
	void applyRecipeCosts();

	const unsigned int CRAFTING_TABLE_SLOTS = 3;

private:
	bool checkRowColumnBounds(int row, int column);

	ItemHandle*** m_craftingTable;
	ItemHandle* m_craftingResult;
	CraftingRecipeLibrary* m_craftingRecipeLibrary;
	CraftingPatternMatchResult* m_matchedRecipeResult;
	ItemGenerator* m_itemGenerator;
};
