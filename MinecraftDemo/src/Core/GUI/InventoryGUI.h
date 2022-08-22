#pragma once
#include "Core/GUI/GUIElement.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Graphics/Graphics.h"
#include <vector>

class InventoryGUI : public GUIElement {
public:
	InventoryGUI(CoreServiceLocator* coreServiceLocator);
	void draw() override;
private:
	void drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImColor sideColor);
	void drawDNDBox(int index, int targetId, float slotSize, ImVec2& windowP0, ImVec2& windowP1);
	void drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture);
	void drawItemCount(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, int count);
	void drawDraggedItem(float slotSize, ImageTexture2D* imageTexture, int count);

	// Percentage of slotSize
	const float SLOT_BORDER_SIZE_PERCENTAGE = 0.07f;
	const float SLOT_SIZE_VIEWPORT_SCALING_FACTOR = 15.0f;
	const unsigned int INVENTORY_STRIDE_SLOTS = 10;

	float m_itemSlotSize;
	float m_inventoryToolbarPadding;
	bool m_isDraggingItem;
	int m_draggedItemIndex;
	ImGuiWindowFlags m_windowFlags;
	ImGuiWindowFlags m_draggedWindowFlags;
	Graphics* m_graphics;
	Inventory* m_inventory;
};
