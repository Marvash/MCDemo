#include "InventoryGUI.h"
#include <imgui/imgui_internal.h>

InventoryGUI::InventoryGUI(CoreServiceLocator* coreServiceLocator) :
	GUIElement(coreServiceLocator),
	m_itemSlotSize(20.0f),
	m_graphics(m_coreServiceLocator->getGraphics()),
	m_inventory(m_coreServiceLocator->getInventory()),
	m_craftingTable(m_coreServiceLocator->getCraftingTable()),
	m_windowFlags(0),
	m_draggedWindowFlags(0),
	m_isDraggingItem(false),
	m_dragSourceItemSlot(nullptr) {
	m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_windowFlags |= ImGuiWindowFlags_NoInputs;
	//m_windowFlags |= ImGuiWindowFlags_MenuBar;
	m_windowFlags |= ImGuiWindowFlags_NoMove;
	m_windowFlags |= ImGuiWindowFlags_NoResize;
	//m_windowFlags |= ImGuiWindowFlags_NoCollapse;
	//m_windowFlags |= ImGuiWindowFlags_NoNav;
	m_windowFlags |= ImGuiWindowFlags_NoBackground;
	m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//m_windowFlags |= ImGuiWindowFlags_UnsavedDocument; {
	m_draggedWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_draggedWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_draggedWindowFlags |= ImGuiWindowFlags_NoInputs;
	//m_draggedWindowFlags |= ImGuiWindowFlags_MenuBar;
	m_draggedWindowFlags |= ImGuiWindowFlags_NoMove;
	m_draggedWindowFlags |= ImGuiWindowFlags_NoResize;
	//m_draggedWindowFlags |= ImGuiWindowFlags_NoCollapse;
	//m_draggedWindowFlags |= ImGuiWindowFlags_NoNav;
	m_draggedWindowFlags |= ImGuiWindowFlags_NoBackground;
	//m_draggedWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//m_draggedWindowFlags |= ImGuiWindowFlags_UnsavedDocument; {
}

InventoryGUI::~InventoryGUI() {
}

void InventoryGUI::draw() {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	if (!player->getIsOpenInventory()) {
		m_isDraggingItem = false;
		return;
	}
	m_inventoryNumSlots = m_inventory->TOTAL_SLOTS;
	m_craftingTableRows = m_craftingTable->CRAFTING_TABLE_SLOTS;
	m_craftingTableCols = m_craftingTable->CRAFTING_TABLE_SLOTS;
	m_viewportWidth = m_graphics->getViewportWidth();
	m_viewportHeight = m_graphics->getViewportHeight();
	m_itemSlotSize = glm::round(m_viewportHeight / SLOT_SIZE_VIEWPORT_SCALING_FACTOR);
	m_windowHorizontalPadding = m_viewportWidth / 60.0f;
	m_windowVerticalPadding = m_viewportHeight / 60.0f;
	m_inventoryToolbarSpacing = m_viewportHeight / 60.0f;
	m_inventoryCraftingTableSpacing = m_inventoryToolbarSpacing;
	m_craftingTableResultHorSpacing = m_itemSlotSize;
	m_inventoryWidth = INVENTORY_STRIDE_SLOTS * m_itemSlotSize;
	m_inventoryHeight = (glm::ceil(m_inventoryNumSlots / (float)INVENTORY_STRIDE_SLOTS) * m_itemSlotSize) + m_inventoryToolbarSpacing;
	m_craftingTableWidth = (m_craftingTableCols * m_itemSlotSize) + m_craftingTableResultHorSpacing + m_itemSlotSize;
	m_craftingTableHeight = m_craftingTableRows * m_itemSlotSize;
	m_windowWidth = (INVENTORY_STRIDE_SLOTS * m_itemSlotSize) + m_windowHorizontalPadding;
	m_windowHeight = m_inventoryHeight + m_inventoryCraftingTableSpacing + m_craftingTableHeight + m_windowVerticalPadding;
	m_windowP0 = ImVec2(glm::round(m_viewportWidth / 2.0f - m_windowWidth / 2.0f), m_viewportHeight / 2.0f - m_windowHeight / 2.0f);
	m_windowP1 = ImVec2(m_windowP0.x + m_windowWidth, m_windowP0.y + m_windowHeight);
	ImGui::SetNextWindowPos(m_windowP0, ImGuiCond_None);
	ImVec2 windowSize = ImVec2(m_windowWidth, m_windowHeight);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_None);
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec2 windowPaddingBackup = style.WindowPadding;
	style.WindowPadding = ImVec2(0.0f, 0.0f);
	ImGui::Begin("Inventory", nullptr, m_windowFlags);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(m_windowP0, m_windowP1, ImColor(0.6f, 0.6f, 0.6f, 1.0f));
	drawInventory();
	drawCraftingTable();
	ImGui::End();
	if (m_isDraggingItem) {
		Item* draggedItem = m_dragSourceItemSlot->getItem();
		ImageTexture2D* icon = nullptr;
		int itemCount = 0;
		if (draggedItem != nullptr) {
			icon = draggedItem->getItemIcon();
			itemCount = draggedItem->getItemCount();
			drawDraggedItem(m_itemSlotSize, icon, itemCount);
		}
	}
	style.WindowPadding = windowPaddingBackup;
}

void InventoryGUI::drawInventory() {
	ImVec2 inventorySize = ImVec2(m_inventoryWidth, m_inventoryHeight);
	ImVec2 inventoryP0(m_windowP0.x + (m_windowHorizontalPadding / 2.0f), m_windowP0.y + (m_windowVerticalPadding / 2.0f) + m_craftingTableHeight + m_inventoryCraftingTableSpacing);
	int strideIndex = 0;
	ImVec2 currentSlotP0(inventoryP0);
	for (int i = 0; i < m_inventoryNumSlots; i++) {
		currentSlotP0.x = inventoryP0.x + glm::round(strideIndex * m_itemSlotSize);
		drawInventoryDNDBox(i, m_itemSlotSize, currentSlotP0);
		drawSlot(m_itemSlotSize, currentSlotP0, ImColor(0.4f, 0.4f, 0.4f, 1.0f));
		ItemSlot* currentItemSlot = m_inventory->getItemSlot(i);
		ImageTexture2D* icon = nullptr;
		int itemCount = 0;
		if (!(currentItemSlot->isEmpty() || (m_isDraggingItem && currentItemSlot == m_dragSourceItemSlot))) {
			icon = currentItemSlot->getItem()->getItemIcon();
			itemCount = currentItemSlot->getItem()->getItemCount();
			drawIcon(m_itemSlotSize, currentSlotP0, icon);
			if (itemCount > 1) {
				drawItemCount(m_itemSlotSize, currentSlotP0, itemCount);
			}
		}
		strideIndex++;
		strideIndex = strideIndex % INVENTORY_STRIDE_SLOTS;
		if (strideIndex == 0) {
			currentSlotP0.y += m_itemSlotSize;
		}
		if (i == m_inventory->getInventorySlots() - 1) {
			currentSlotP0.y += m_inventoryToolbarPadding;
		}
	}
}

void InventoryGUI::resetDNDLogic() {
	m_dragSourceItemSlot = nullptr;
	m_isDraggingItem = false;
}

void InventoryGUI::drawCraftingTable() {
	ImVec2 craftingTableSize = ImVec2(m_craftingTableWidth, m_craftingTableHeight);
	ImVec2 craftingTableP0(m_windowP0.x + ((m_windowWidth / 2.0f) - (craftingTableSize.x / 2.0f)), m_windowP0.y + (m_windowVerticalPadding / 2.0f));
	ImVec2 craftingTableP1(craftingTableP0.x + craftingTableSize.x, craftingTableP0.y + craftingTableSize.y);
	ImVec2 currentSlotP0(craftingTableP0);
	for (int row = 0; row < m_craftingTableRows; row++) {
		for (int col = 0; col < m_craftingTableCols; col++) {
			currentSlotP0.x = craftingTableP0.x + glm::round(col * m_itemSlotSize);
			currentSlotP0.y = craftingTableP0.y + glm::round(row * m_itemSlotSize);
			int targetId = (row * m_craftingTableCols) + col;
			drawCraftingTableDNDBox(targetId, m_itemSlotSize, currentSlotP0);
			drawSlot(m_itemSlotSize, currentSlotP0, ImColor(0.4f, 0.4f, 0.4f, 1.0f));
			ItemSlot* currentItemSlot = m_craftingTable->getItemSlot(targetId);
			ImageTexture2D* icon = nullptr;
			int itemCount = 0;
			if (!(currentItemSlot->isEmpty() || (m_isDraggingItem && currentItemSlot == m_dragSourceItemSlot))) {
				icon = currentItemSlot->getItem()->getItemIcon();
				itemCount = currentItemSlot->getItem()->getItemCount();
				drawIcon(m_itemSlotSize, currentSlotP0, icon);
				if (itemCount > 1) {
					drawItemCount(m_itemSlotSize, currentSlotP0, itemCount);
				}
			}
		}
	}
	currentSlotP0.x = craftingTableP0.x + glm::round(m_craftingTableCols * m_itemSlotSize) + m_craftingTableResultHorSpacing;
	currentSlotP0.y = craftingTableP0.y;
	if (m_craftingTableRows % 2 == 0) {
		currentSlotP0.y += ((float)m_craftingTableRows / 2.0f) * m_itemSlotSize;
	}
	else {
		currentSlotP0.y += ((int)m_craftingTableRows / 2) * m_itemSlotSize;
	}
	drawResultDNDBox(m_itemSlotSize, currentSlotP0);
	drawSlot(m_itemSlotSize, currentSlotP0, ImColor(0.4f, 0.4f, 0.4f, 1.0f));
	ItemSlot* currentItemSlot = m_craftingTable->getResultItemSlot();
	ImageTexture2D* icon = nullptr;
	int itemCount = 0;
	if (!(currentItemSlot->isEmpty() || (m_isDraggingItem && currentItemSlot == m_dragSourceItemSlot))) {
		icon = currentItemSlot->getItem()->getItemIcon();
		itemCount = currentItemSlot->getItem()->getItemCount();
		drawIcon(m_itemSlotSize, currentSlotP0, icon);
		if (itemCount > 1) {
			drawItemCount(m_itemSlotSize, currentSlotP0, itemCount);
		}
	}
}

void InventoryGUI::drawSlot(float slotSize, ImVec2& windowP0, ImColor sideColor) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 rectP0, rectP1;
	rectP0 = ImVec2(windowP0.x, windowP0.y);
	rectP1 = ImVec2(windowP0.x + rectWidth, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + rectWidth, windowP0.y);
	rectP1 = ImVec2(windowP0.x + (slotSize - rectWidth), windowP0.y + rectWidth);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + (slotSize - rectWidth), windowP0.y);
	rectP1 = ImVec2(windowP0.x + slotSize, windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
	rectP0 = ImVec2(windowP0.x + rectWidth, windowP0.y + (slotSize - rectWidth));
	rectP1 = ImVec2(windowP0.x + (slotSize - rectWidth), windowP0.y + slotSize);
	drawList->AddRectFilled(rectP0, rectP1, sideColor);
}

void InventoryGUI::drawInventoryDNDBox(int targetId, float slotSize, ImVec2& windowP0) {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 popupColorBackup = style.Colors[4];
	ImVec4 buttonColorBackup = style.Colors[22];
	ImVec4 buttonHoverColorBackup = style.Colors[23];
	ImVec4 buttonActiveColorBackup = style.Colors[24];
	float popupBorderSizeBackup = style.PopupBorderSize;
	style.Colors[4].w = 0.0f;
	style.Colors[21].w = 0.0f;
	style.Colors[22] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);
	style.Colors[23].w = 0.0f;
	style.PopupBorderSize = 0.0f;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, targetSize;
	p0 = ImVec2(windowP0.x, windowP0.y);
	targetSize = ImVec2(slotSize, slotSize);
	ImGui::PushID(targetId);
	ImGui::SetCursorScreenPos(p0);
	ImGui::BeginChild("InventoryDNDChild", targetSize);
	ImGui::Button("##DNDButton", targetSize);
	if (ImGui::IsItemActivated()) {
		if (!m_isDraggingItem) {
			if (!m_inventory->getItemSlot(targetId)->isEmpty()) {
				m_isDraggingItem = true;
				m_dragSourceItemSlot = m_inventory->getItemSlot(targetId);
			}
		}
		else {
			ItemSlot* m_dragTargetItemSlot = m_inventory->getItemSlot(targetId);
			if (m_dragSourceItemSlot == m_craftingTable->getResultItemSlot()) {
				if (m_inventory->getItemSlot(targetId)->isEmpty()) {
					m_craftingTable->fulfillMatchingRecipeContract();
					m_craftingTable->matchRecipe();
				}
			}
			else {
				m_dragTargetItemSlot->resolveSlotDrag(m_dragSourceItemSlot);
				m_craftingTable->matchRecipe();
			}
			resetDNDLogic();
		}
	}
	ImGui::EndChild();
	ImGui::PopID();
	style.PopupBorderSize = popupBorderSizeBackup;
	style.Colors[4] = popupColorBackup;
	style.Colors[21] = buttonColorBackup;
	style.Colors[22] = buttonHoverColorBackup;
	style.Colors[23] = buttonActiveColorBackup;
}

void InventoryGUI::drawCraftingTableDNDBox(int targetId, float slotSize, ImVec2& windowP0) {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 popupColorBackup = style.Colors[4];
	ImVec4 buttonColorBackup = style.Colors[22];
	ImVec4 buttonHoverColorBackup = style.Colors[23];
	ImVec4 buttonActiveColorBackup = style.Colors[24];
	float popupBorderSizeBackup = style.PopupBorderSize;
	style.Colors[4].w = 0.0f;
	style.Colors[21].w = 0.0f;
	style.Colors[22] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);
	style.Colors[23].w = 0.0f;
	style.PopupBorderSize = 0.0f;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, targetSize;
	p0 = ImVec2(windowP0.x, windowP0.y);
	targetSize = ImVec2(slotSize, slotSize);
	ImGui::PushID(targetId);
	ImGui::SetCursorScreenPos(p0);
	ImGui::BeginChild("craftingDNDChild", targetSize);
	ImGui::Button("##DNDButton", targetSize);
	if (ImGui::IsItemActivated()) {
		if (!m_isDraggingItem) {
			if (!m_craftingTable->getItemSlot(targetId)->isEmpty()) {
				m_isDraggingItem = true;
				m_dragSourceItemSlot = m_craftingTable->getItemSlot(targetId);
			}
		}
		else {
			ItemSlot* m_dragTargetItemSlot = m_craftingTable->getItemSlot(targetId);
			if (m_dragSourceItemSlot == m_craftingTable->getResultItemSlot()) {
				if (m_inventory->getItemSlot(targetId)->isEmpty()) {
					m_craftingTable->fulfillMatchingRecipeContract();
					m_craftingTable->matchRecipe();
				}
			}
			else {
				m_dragTargetItemSlot->resolveSlotDrag(m_dragSourceItemSlot);
				m_craftingTable->matchRecipe();
			}
			resetDNDLogic();
		}
	}
	ImGui::EndChild();
	ImGui::PopID();
	style.PopupBorderSize = popupBorderSizeBackup;
	style.Colors[4] = popupColorBackup;
	style.Colors[21] = buttonColorBackup;
	style.Colors[22] = buttonHoverColorBackup;
	style.Colors[23] = buttonActiveColorBackup;
}

void InventoryGUI::drawResultDNDBox(float slotSize, ImVec2& windowP0) {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 popupColorBackup = style.Colors[4];
	ImVec4 buttonColorBackup = style.Colors[22];
	ImVec4 buttonHoverColorBackup = style.Colors[23];
	ImVec4 buttonActiveColorBackup = style.Colors[24];
	float popupBorderSizeBackup = style.PopupBorderSize;
	style.Colors[4].w = 0.0f;
	style.Colors[21].w = 0.0f;
	style.Colors[22] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);
	style.Colors[23].w = 0.0f;
	style.PopupBorderSize = 0.0f;
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, targetSize;
	p0 = ImVec2(windowP0.x, windowP0.y);
	targetSize = ImVec2(slotSize, slotSize);
	ImGui::PushID("Result");
	ImGui::SetCursorScreenPos(p0);
	ImGui::BeginChild("ResultDNDChild", targetSize);
	ImGui::Button("##DNDButton", targetSize);
	if (ImGui::IsItemActivated()) {
		if (!m_isDraggingItem) {
			if (!m_craftingTable->getResultItemSlot()->isEmpty()) {
				m_isDraggingItem = true;
				m_dragSourceItemSlot = m_craftingTable->getResultItemSlot();
			}
		}
	}
	ImGui::EndChild();
	ImGui::PopID();
	style.PopupBorderSize = popupBorderSizeBackup;
	style.Colors[4] = popupColorBackup;
	style.Colors[21] = buttonColorBackup;
	style.Colors[22] = buttonHoverColorBackup;
	style.Colors[23] = buttonActiveColorBackup;
}

void InventoryGUI::drawDraggedItem(float slotSize, ImageTexture2D* imageTexture, int count) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImVec2 mousePos(ImGui::GetIO().MousePos); 
	ImVec2 windowSize(slotSize - (rectWidth * 2), slotSize - (rectWidth * 2));
	ImVec2 windowP0(mousePos.x - (windowSize.x / 2.0f), mousePos.y - (windowSize.y / 2.0f));
	ImVec2 itemCountP0(windowP0.x + slotSize - (rectWidth * 4), windowP0.y + slotSize - (rectWidth * 4));
	ImGui::SetNextWindowPos(windowP0);
	ImGui::Begin("DraggedWindow", nullptr, m_draggedWindowFlags);
	ImGui::Image((void*)(intptr_t)imageTexture->m_id, windowSize, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::SetCursorScreenPos(itemCountP0);
	if (count > 1) {
		ImGui::Text("%d", count);
	}
	ImGui::End();
}

void InventoryGUI::drawIcon(float slotSize, ImVec2& windowP0, ImageTexture2D* imageTexture) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 p0, iconSize;
	p0 = ImVec2(windowP0.x + rectWidth, windowP0.y + rectWidth);
	iconSize = ImVec2(slotSize - (rectWidth * 2.0f), slotSize - (rectWidth * 2.0f));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Image((void*)(intptr_t)imageTexture->m_id, iconSize, ImVec2(0, 1), ImVec2(1, 0));
}

void InventoryGUI::drawItemCount(float slotSize, ImVec2& windowP0, int count) {
	float rectWidth = glm::round(slotSize * SLOT_BORDER_SIZE_PERCENTAGE);
	ImVec2 p0(windowP0.x + slotSize - (rectWidth * 4), windowP0.y + slotSize - (rectWidth * 4));
	ImGui::SetCursorScreenPos(p0);
	ImGui::Text("%d", count);
}