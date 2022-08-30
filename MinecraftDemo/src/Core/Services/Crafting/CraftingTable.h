#pragma once
#include "Core/Services/ItemLibrary/ItemSlot.h"
#include "CraftingRecipeLibrary.h"
#include "Core/Exceptions/GameLogicException.h"

class CraftingTable : public CoreService {
public:
	CraftingTable(CoreEventDispatcher* coreEventDispatcher);
	~CraftingTable();
	void init(CraftingRecipeLibrary* craftingRecipeLibrary);
	void onNotify(Event& newEvent) override;
	ItemSlot* getItemSlot(int row, int column);
	ItemSlot* getItemSlot(int index);
	ItemSlot* getResultItemSlot();
	void matchRecipe();
	void fulfillMatchingRecipeContract();

	const unsigned int CRAFTING_TABLE_SLOTS = 3;

private:
	bool checkRowColumnBounds(int row, int column);

	ItemSlot*** m_craftingTable;
	ItemSlot* m_craftingResult;
	CraftingRecipe* m_matchingRecipe;
	CraftingRecipeLibrary* m_craftingRecipeLibrary;
};
