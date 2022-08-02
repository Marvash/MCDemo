#include "Inventory.h"
#include <imgui/imgui_internal.h>
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
	unsigned int numSlots = inventoryManager->TOTAL_SLOTS;
	float viewportWidth = m_graphics->getViewportWidth();
	float viewportHeight = m_graphics->getViewportHeight();
	m_itemSlotSize = glm::round(viewportHeight / SLOT_SIZE_VIEWPORT_SCALING_FACTOR);
	float inventoryWidthOffset = viewportWidth / 60.0f;
	float inventoryHeightOffset = viewportHeight / 60.0f;
	float inventoryToolbarPadding = viewportHeight / 60.0f;
	float windowWidth = (INVENTORY_STRIDE_SLOTS * m_itemSlotSize) + inventoryWidthOffset;
	float windowHeight = (glm::ceil(numSlots / (float)INVENTORY_STRIDE_SLOTS) * m_itemSlotSize) + inventoryHeightOffset + inventoryToolbarPadding;
	float inventoryWidth = INVENTORY_STRIDE_SLOTS * m_itemSlotSize;
	float inventoryHeight = (glm::ceil(numSlots / (float)INVENTORY_STRIDE_SLOTS) * m_itemSlotSize) + inventoryToolbarPadding;
	ImVec2 windowP0(glm::round(viewportWidth / 2.0f - windowWidth / 2.0f), viewportHeight / 2.0f - windowHeight / 2.0f);
	ImVec2 inventoryP0(glm::round(viewportWidth / 2.0f - inventoryWidth / 2.0f), viewportHeight / 2.0f - inventoryHeight / 2.0f);
	ImGui::SetNextWindowPos(windowP0, ImGuiCond_None);
	ImVec2 windowSize = ImVec2(windowWidth, windowHeight);
	ImVec2 inventorySize = ImVec2(inventoryWidth, inventoryHeight);
	ImVec2 windowP1(windowP0.x + windowSize.x, windowP0.y + windowSize.y);
	ImVec2 inventoryP1(inventoryP0.x + inventorySize.x, inventoryP0.y + inventorySize.y);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_None);
	ImGui::Begin("Inventory", nullptr, m_windowFlags);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(windowP0, windowP1, ImColor(0.6f, 0.6f, 0.6f, 1.0f));
	int strideIndex = 0;
	for (int i = 0; i < numSlots; i++) {
		drawSlot(strideIndex, m_itemSlotSize, inventoryP0, inventoryP1, ImColor(0.4f, 0.4f, 0.4f, 1.0f));
		Item* currentItem = inventoryManager->getItemInSlot(i);
		ImageTexture2D* icon = nullptr;
		if (currentItem != nullptr) {
			Item::ItemType type = currentItem->getItemType();
			switch (type) {
				case Item::ItemType::CUBE: {
					CubeItem* currentCubeItem = static_cast<CubeItem*>(currentItem);
					icon = m_iconManager->getIcon(currentCubeItem->getCubeId());
					drawIcon(strideIndex, m_itemSlotSize, inventoryP0, inventoryP1, icon);
					break;
				}
			}
			if (currentItem->getCount() > 1) {
				drawItemCount(strideIndex, m_itemSlotSize, inventoryP0, inventoryP1, currentItem->getCount());
			}
		}
		drawDNDBox(strideIndex, i, m_itemSlotSize, inventoryP0, inventoryP1, icon);
		strideIndex++;
		strideIndex = strideIndex % INVENTORY_STRIDE_SLOTS;
		if (strideIndex == 0) {
			inventoryP0.y += m_itemSlotSize;
			inventoryP1.y += m_itemSlotSize;
		}
		if (i == inventoryManager->getInventorySlots() - 1) {
			inventoryP0.y += inventoryToolbarPadding;
			inventoryP1.y += inventoryToolbarPadding;
		}
	}
	ImGui::End();
}

void Inventory::drawSlot(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImColor sideColor) {
	float windowWidth = windowP1.x - windowP0.x;
	float windowHeight = windowP1.y - windowP0.y;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 rectP0, rectP1;
	rectP0 = ImVec2(windowP0.x + indexOffset, windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y);
	rectP1 = ImVec2(windowP0.x + indexOffset + slotSize, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + (slotSize - rectWidth));
	rectP1 = ImVec2(windowP0.x + indexOffset + (slotSize - rectWidth), windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
}

void Inventory::drawDNDBox(int index, int targetId, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture) {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	InventoryManager* inventoryManager = player->getInventoryManager();
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, targetSize;
	p0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + rectWidth);
	targetSize = ImVec2(slotSize - (rectWidth * 2.0f), slotSize - (rectWidth * 2.0f));
	ImGui::PushID(targetId);
	ImGui::SetCursorScreenPos(p0);
	ImGui::BeginChild("DNDChild", targetSize);
	ImGui::InvisibleButton("DNDTargetButton", targetSize);
	if (inventoryManager->getItemInSlot(targetId) != nullptr) {
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("INVENTORY_DND", &targetId, sizeof(int));
			if (imageTexture != nullptr) {
				ImGui::Image((void*)(intptr_t)imageTexture->m_id, targetSize, ImVec2(0, 1), ImVec2(1, 0));
			}
			ImGui::EndDragDropSource();
		}
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("INVENTORY_DND"))
		{
			if (payload->DataSize == sizeof(int)) {
				int inventoryIndex = *(const int*)payload->Data;
				inventoryManager->swapItems(inventoryIndex, targetId);
			}
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::EndChild();
	ImGui::PopID();
}

void Inventory::drawIcon(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, ImageTexture2D* imageTexture) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, iconSize;
	p0 = ImVec2(windowP0.x + indexOffset + rectWidth, windowP0.y + rectWidth);
	iconSize = ImVec2(slotSize - (rectWidth * 2.0f), slotSize - (rectWidth * 2.0f));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Image((void*)(intptr_t)imageTexture->m_id, iconSize, ImVec2(0, 1), ImVec2(1, 0));
}

void Inventory::drawItemCount(int index, float slotSize, ImVec2& windowP0, ImVec2& windowP1, int count) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	float indexOffset = glm::round(index * slotSize);
	ImVec2 p0(windowP0.x + indexOffset + slotSize - (rectWidth * 4), windowP0.y + slotSize - (rectWidth * 4));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Text("%d", count);
}