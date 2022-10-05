#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ItemLibrary/ItemGenerator.h"
#include "Core/Services/ItemLibrary/ItemHandle.h"
#include "Core/Services/Crafting/CraftingTable.h"
#include "Inventory.h"
#include "Core/Services/Input/InputEnums.h"
#include <glm/glm.hpp>
#include <vector>

class InventoryUIInteractions {
public:
	InventoryUIInteractions(Inventory* inventory, CraftingTable* craftingTable);
	void handleInventorySlotClick(int slotIndex, InputMouseButton mouseButton);
	void handleCraftingTableSlotClick(int slotIndex, InputMouseButton mouseButton);
	void handleCraftingResultSlotClick();
	bool isDraggingItem();
	ItemHandle* getDraggedItem();
	void resetDNDLogic();
private:
	Inventory* m_inventory;
	CraftingTable* m_craftingTable;
	bool m_isDraggingItem;
	ItemHandle* m_dragSourceItemSlot;
};