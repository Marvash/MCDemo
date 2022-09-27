#pragma once
#include "Core/GUI/GUIElement.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Graphics/Graphics.h"
#include <vector>

class InventoryGUI : public GUIElement {
public:
	InventoryGUI(CoreServiceLocator* coreServiceLocator);
	~InventoryGUI();
	void draw() override;
private:
	void drawInventory();
	void drawCraftingTable();
	void drawSlot(float slotSize, ImVec2& windowP0, ImColor sideColor);
	void drawInventoryDNDBox(int targetId, float slotSize, ImVec2& windowP0);
	void drawCraftingTableDNDBox(int targetId, float slotSize, ImVec2& windowP0);
	void drawResultDNDBox(float slotSize, ImVec2& windowP0);
	void drawIcon(float slotSize, ImVec2& windowP0, ImageTexture2D* imageTexture);
	void drawItemCount(float slotSize, ImVec2& windowP0, int count);
	void drawDraggedItem(float slotSize, ImageTexture2D* imageTexture, int count);
	void resetDNDLogic();

	// Percentage of slotSize
	const float SLOT_BORDER_SIZE_PERCENTAGE = 0.07f;
	const float SLOT_SIZE_VIEWPORT_SCALING_FACTOR = 15.0f;
	const unsigned int INVENTORY_STRIDE_SLOTS = 10;

	float m_itemSlotSize;
	float m_inventoryToolbarPadding;
	bool m_isDraggingItem;
	bool m_isDraggingCraftingResult;
	int m_inventoryDraggedItemIndex;
	int m_craftingTableDraggedItemIndex;
	float m_windowHorizontalPadding;
	float m_windowVerticalPadding;
	float m_inventoryToolbarSpacing;
	float m_inventoryCraftingTableSpacing;
	float m_inventoryWidth;
	float m_inventoryHeight;
	float m_craftingTableWidth;
	float m_craftingTableHeight;
	float m_craftingTableResultHorSpacing;
	float m_windowWidth;
	float m_windowHeight;
	unsigned int m_inventoryNumSlots;
	unsigned int m_craftingTableRows;
	unsigned int m_craftingTableCols;
	float m_viewportWidth;
	float m_viewportHeight;
	ItemHandle* m_dragSourceItemSlot;
	ImVec2 m_windowP0;
	ImVec2 m_windowP1;
	ImGuiWindowFlags m_windowFlags;
	ImGuiWindowFlags m_draggedWindowFlags;
	Graphics* m_graphics;
	Inventory* m_inventory;
	CraftingTable* m_craftingTable;
};
