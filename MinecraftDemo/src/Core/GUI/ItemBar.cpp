#include "ItemBar.h"

ItemBar::ItemBar(CoreServiceLocator* coreServiceLocator, unsigned int numSlots, IconManager* iconManager) :
	GUIElement(coreServiceLocator),
	m_itemSlotSize(20.0f),
	m_numSlots(numSlots),
	m_selectedSlot(0),
	m_graphics(m_coreServiceLocator->getGraphics()),
	m_iconManager(iconManager) {
	m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_windowFlags |= ImGuiWindowFlags_NoInputs;
	//m_windowFlags |= ImGuiWindowFlags_MenuBar;
	m_windowFlags |= ImGuiWindowFlags_NoMove;
	m_windowFlags |= ImGuiWindowFlags_NoResize;
	//m_windowFlags |= ImGuiWindowFlags_NoCollapse;
	//m_windowFlags |= ImGuiWindowFlags_NoNav;
	m_windowFlags |= ImGuiWindowFlags_NoBackground;
	//m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//m_windowFlags |= ImGuiWindowFlags_UnsavedDocument;
}

void ItemBar::setSelectedSlot(unsigned int index) {
	m_selectedSlot = index;
}

void ItemBar::draw() {
	float viewportWidth = m_graphics->getViewportWidth();
	float viewportHeight = m_graphics->getViewportHeight();
	m_itemSlotSize = glm::round(viewportHeight / SLOT_SIZE_VIEWPORT_DENOM);
	float widthPadding = glm::round(m_itemSlotSize * SLOT_BORDER_SIZE_PERCENTAGE * 4.0f);
	float heightPadding = glm::round(m_itemSlotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float windowWidth = m_numSlots * m_itemSlotSize;
	float paddedWindowWidth = windowWidth + widthPadding;
	float windowHeight = m_itemSlotSize;
	float paddedWindowHeight = windowHeight + heightPadding;
	ImVec2 windowP0(glm::round(viewportWidth / 2.0f - paddedWindowWidth / 2.0f), viewportHeight - paddedWindowHeight);
	ImGui::SetNextWindowPos(windowP0, ImGuiCond_None);
	ImVec2 windowSize = ImVec2(paddedWindowWidth, paddedWindowHeight);
	ImVec2 windowP1(windowP0.x + windowSize.x, windowP0.y + windowSize.y);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_None);
	ImGui::Begin("ItemBar", nullptr, m_windowFlags);
	windowP0 = ImVec2(glm::round(viewportWidth / 2.0f - windowWidth / 2.0f), viewportHeight - windowHeight);
	windowSize = ImVec2(windowWidth, windowHeight);
	windowP1 = ImVec2(windowP0.x + windowSize.x, windowP0.y + windowSize.y);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(windowP0, windowP1, ImColor(0.0f, 0.0f, 0.0f, 0.3f));
	for (int i = 0; i < m_numSlots; i++) {
		drawSlot(i, m_itemSlotSize, windowP0, windowP1);
		if ((i % 2) == 0) {
			drawIcon(i, m_itemSlotSize, windowP0, windowP1, m_iconManager->getIcon(Cube::CubeId::SAND_BLOCK));
		}
		else {
			drawIcon(i, m_itemSlotSize, windowP0, windowP1, m_iconManager->getIcon(Cube::CubeId::DIRT_BLOCK));
		}
	}
	drawSelectedSlot(m_selectedSlot, m_itemSlotSize, windowP0, windowP1);
	ImGui::End();
}

void ItemBar::drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1) {
	float windowWidth = windowP1.x - windowP0.x;
	float windowHeight = windowP1.y - windowP0.y;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 rectP0, rectP1;
	rectP0 = ImVec2(windowP0.x + indexOffset, windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(160, 160, 160));
	rectP0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(160, 160, 160));
	rectP0 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + slotSize, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(160, 160, 160));
	rectP0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + (slotSize - rectWidth));
	rectP1 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(160, 160, 160));
}

void ItemBar::drawSelectedSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1) {
	float windowWidth = windowP1.x - windowP0.x;
	float windowHeight = windowP1.y - windowP0.y;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 rectP0, rectP1;
	rectP0 = ImVec2(windowP0.x + indexOffset - rectWidth, windowP0.y - rectWidth);
	rectP1 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + slotSize + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(230, 230, 230));
	rectP0 = ImVec2(windowP0.x + indexOffset - rectWidth, windowP0.y - rectWidth);
	rectP1 = ImVec2(windowP0.x + indexOffset + slotSize, windowP0.y + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(230, 230, 230));
	rectP0 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y - rectWidth);
	rectP1 = ImVec2(windowP0.x + indexOffset + slotSize + rectWidth, windowP0.y + slotSize + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(230, 230, 230));
	rectP0 = ImVec2(windowP0.x + indexOffset - rectWidth, windowP0.y + (slotSize - rectWidth));
	rectP1 = ImVec2(windowP0.x + indexOffset + slotSize, windowP0.y + slotSize + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, ImColor(230, 230, 230));
}

void ItemBar::drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, iconSize;
	p0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + rectWidth);
	iconSize = ImVec2(slotSize - (rectWidth * 2.0f), slotSize - (rectWidth * 2.0f));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Image((void*)(intptr_t)imageTexture->m_id, iconSize);
}