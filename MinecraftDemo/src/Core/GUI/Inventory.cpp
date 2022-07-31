#include "Inventory.h"

Inventory::Inventory(CoreServiceLocator* coreServiceLocator, IconManager* iconManager) : 
	GUIElement(coreServiceLocator),
	m_itemSlotSize(20.0f),
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
	//m_windowFlags |= ImGuiWindowFlags_UnsavedDocument; {

}

void Inventory::draw() {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	if (!player->getIsOpenInventory()) {
		return;
	}
	InventoryManager* inventoryManager = player->getInventoryManager();
	unsigned int numSlots = inventoryManager->getInventorySlots();
	float viewportWidth = m_graphics->getViewportWidth();
	float viewportHeight = m_graphics->getViewportHeight();
	m_itemSlotSize = glm::round(viewportHeight / SLOT_SIZE_VIEWPORT_SCALING_FACTOR);
	float widthPadding = glm::round(m_itemSlotSize * SLOT_BORDER_SIZE_PERCENTAGE * 4.0f);
	float heightPadding = glm::round(m_itemSlotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float windowWidth = INVENTORY_STRIDE_SLOTS * m_itemSlotSize;
	float windowHeight = glm::ceil(numSlots / (float)INVENTORY_STRIDE_SLOTS) * m_itemSlotSize;
	ImVec2 windowP0(glm::round(viewportWidth / 2.0f - windowWidth / 2.0f), viewportHeight / 2.0f - windowHeight / 2.0f);
	ImGui::SetNextWindowPos(windowP0, ImGuiCond_None);
	ImVec2 windowSize = ImVec2(windowWidth, windowHeight);
	ImVec2 windowP1(windowP0.x + windowSize.x, windowP0.y + windowSize.y);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_None);
	ImGui::Begin("Inventory", nullptr, m_windowFlags);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(windowP0, windowP1, ImColor(0.6f, 0.6f, 0.6f, 1.0f));
	/*
	for (int i = 0; i < numSlots; i++) {
		drawSlot(i, m_itemSlotSize, windowP0, windowP1);
		Item* currentItem = itemBar[i];
		if (currentItem != nullptr) {
			Item::ItemType type = currentItem->getItemType();
			switch (type) {
			case Item::ItemType::CUBE: {
				CubeItem* currentCubeItem = static_cast<CubeItem*>(currentItem);
				drawIcon(i, m_itemSlotSize, windowP0, windowP1, m_iconManager->getIcon(currentCubeItem->getCubeId()));
				break;
			}
			}
			if (currentItem->getCount() > 1) {
				drawItemCount(i, m_itemSlotSize, windowP0, windowP1, currentItem->getCount());
			}
		}
	}
	*/
	ImGui::End();
}

void Inventory::drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1) {
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

void Inventory::drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, iconSize;
	p0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + rectWidth);
	iconSize = ImVec2(slotSize - (rectWidth * 2.0f), slotSize - (rectWidth * 2.0f));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Image((void*)(intptr_t)imageTexture->m_id, iconSize);
}

void Inventory::drawItemCount(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, int count) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImVec2 p0(windowP0.x + indexOffset + slotSize - (rectWidth * 4), windowP0.y + slotSize - (rectWidth * 4));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Text("%d", count);
}