#pragma once
#include "Core/GUI/GUIElement.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Graphics/Graphics.h"
#include "Core/Services/ItemLibrary/IconLibrary/IconLibrary.h"
#include <vector>

class ItemBar : public GUIElement {
public:
	ItemBar(CoreServiceLocator* coreServiceLocator);
	void draw() override;
private:
	void drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1);
	void drawSelectedSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1);
	void drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture);
	void drawItemCount(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, int count);

	// Percentage of slotSize
	const float SLOT_BORDER_SIZE_PERCENTAGE = 0.07f;
	const float SLOT_SIZE_VIEWPORT_SCALING_FACTOR = 15.0f;
	
	float m_itemSlotSize;
	ImGuiWindowFlags m_windowFlags;
	Graphics* m_graphics;
	IconLibrary* m_iconLibrary;
};