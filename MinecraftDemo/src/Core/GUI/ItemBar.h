#pragma once
#include "Core/GUI/GUIElement.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Graphics/Graphics.h"
#include "Core/IconManager/IconManager.h"
#include <vector>

class ItemBar : public GUIElement {
public:
	ItemBar(CoreServiceLocator* coreServiceLocator, unsigned int numSlots, IconManager* iconManager);
	void draw() override;
	void setSelectedSlot(unsigned int index);
private:
	void drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1);
	void drawSelectedSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1);
	void drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture);

	// Percentage of slotSize
	const float SLOT_BORDER_SIZE_PERCENTAGE = 0.07f;
	const float SLOT_SIZE_VIEWPORT_DENOM = 15.0f;
	
	float m_itemSlotSize;
	unsigned int m_numSlots;
	unsigned int m_selectedSlot;
	ImGuiWindowFlags m_windowFlags;
	Graphics* m_graphics;
	IconManager* m_iconManager;
};