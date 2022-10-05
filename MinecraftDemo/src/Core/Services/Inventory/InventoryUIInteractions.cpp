#include "InventoryUIInteractions.h"

InventoryUIInteractions::InventoryUIInteractions(Inventory* inventory, CraftingTable* craftingTable) :
	m_inventory(inventory),
	m_craftingTable(craftingTable),
	m_isDraggingItem(false),
	m_dragSourceItemSlot(nullptr) {
}

void InventoryUIInteractions::handleInventorySlotClick(int slotIndex, InputMouseButton mouseButton) {
	switch (mouseButton)
	{
		case InputMouseButton::MOUSE_LEFT: {
			if (!m_isDraggingItem) {
				if (!m_inventory->getItemInSlot(slotIndex)->isNullItem()) {
					m_isDraggingItem = true;
					m_dragSourceItemSlot = m_inventory->getItemInSlot(slotIndex);
				}
			}
			else {
				ItemHandle* dragTargetItemSlot = m_inventory->getItemInSlot(slotIndex);
				if (m_dragSourceItemSlot == m_craftingTable->getResultItemSlot()) {
					if (dragTargetItemSlot->isNullItem()) {
						dragTargetItemSlot->swapHandle(m_dragSourceItemSlot);
						m_craftingTable->applyRecipeCosts();
						m_craftingTable->matchRecipe();
					}
				}
				else if (dragTargetItemSlot->isCompatibleWith(m_dragSourceItemSlot)) {
					dragTargetItemSlot->mergeWithHandle(m_dragSourceItemSlot);
					m_craftingTable->matchRecipe();
				}
				else {
					dragTargetItemSlot->swapHandle(m_dragSourceItemSlot);
					m_craftingTable->matchRecipe();
				}
				resetDNDLogic();
			}
			break;
			}
		case InputMouseButton::MOUSE_RIGHT: {
			if (!m_isDraggingItem) {
				m_inventory->splitItemInSlot(slotIndex);
			}
			else {
				ItemHandle* dragTargetItemSlot = m_inventory->getItemInSlot(slotIndex);
				if (dragTargetItemSlot == m_dragSourceItemSlot) {
					m_inventory->splitItemInSlot(slotIndex);
				}
				else if (dragTargetItemSlot->isCompatibleWith(m_dragSourceItemSlot)) {
					dragTargetItemSlot->addToItemCount(1);
					m_dragSourceItemSlot->subtractToItemCount(1);
					if (m_dragSourceItemSlot->isNullItem()) {
						resetDNDLogic();
					}
					m_craftingTable->matchRecipe();
				}
				else if (dragTargetItemSlot->isNullItem()) {
					m_inventory->addItemInEmptyInventorySlot(m_dragSourceItemSlot->getItemId(), 1, slotIndex);
					m_dragSourceItemSlot->subtractToItemCount(1);
					if (m_dragSourceItemSlot->isNullItem()) {
						resetDNDLogic();
					}
					m_craftingTable->matchRecipe();
				}
			}
			break;
			}
		default:
			break;
	}
}

void InventoryUIInteractions::handleCraftingTableSlotClick(int slotIndex, InputMouseButton mouseButton) {
	switch (mouseButton)
	{
		case InputMouseButton::MOUSE_LEFT: {
			if (!m_isDraggingItem) {
				if (!m_craftingTable->getItemSlot(slotIndex)->isNullItem()) {
					m_isDraggingItem = true;
					m_dragSourceItemSlot = m_craftingTable->getItemSlot(slotIndex);
				}
			}
			else {
				ItemHandle* dragTargetItemSlot = m_craftingTable->getItemSlot(slotIndex);
				if (m_dragSourceItemSlot == m_craftingTable->getResultItemSlot()) {
					if (dragTargetItemSlot->isNullItem()) {
						dragTargetItemSlot->swapHandle(m_dragSourceItemSlot);
						m_craftingTable->applyRecipeCosts();
						m_craftingTable->matchRecipe();
					}
				}
				else if (dragTargetItemSlot->isCompatibleWith(m_dragSourceItemSlot)) {
					dragTargetItemSlot->mergeWithHandle(m_dragSourceItemSlot);
					m_craftingTable->matchRecipe();
				}
				else {
					dragTargetItemSlot->swapHandle(m_dragSourceItemSlot);
					m_craftingTable->matchRecipe();
				}
				resetDNDLogic();
			}
			break;
		}
		case InputMouseButton::MOUSE_RIGHT: {
			if (!m_isDraggingItem) {
				m_craftingTable->splitItemSlot(slotIndex);
				m_craftingTable->matchRecipe();
			}
			else {
				ItemHandle* dragTargetItemSlot = m_craftingTable->getItemSlot(slotIndex);
				if (dragTargetItemSlot == m_dragSourceItemSlot) {
					m_craftingTable->splitItemSlot(slotIndex);
				}
				else if (dragTargetItemSlot->isCompatibleWith(m_dragSourceItemSlot)) {
					dragTargetItemSlot->addToItemCount(1);
					m_dragSourceItemSlot->subtractToItemCount(1);
					if (m_dragSourceItemSlot->isNullItem()) {
						resetDNDLogic();
					}
					m_craftingTable->matchRecipe();
				}
				else if (dragTargetItemSlot->isNullItem()) {

					m_craftingTable->addItemInEmptyCraftingSlot(m_dragSourceItemSlot->getItemId(), 1, slotIndex);
					m_dragSourceItemSlot->subtractToItemCount(1);
					if (m_dragSourceItemSlot->isNullItem()) {
						resetDNDLogic();
					}
					m_craftingTable->matchRecipe();
				}
			}
			break;
		}
		default:
			break;
	}
}

void InventoryUIInteractions::handleCraftingResultSlotClick() {
	if (!m_isDraggingItem) {
		if (!m_craftingTable->getResultItemSlot()->isNullItem()) {
			m_isDraggingItem = true;
			m_dragSourceItemSlot = m_craftingTable->getResultItemSlot();
		}
	}
}

void InventoryUIInteractions::resetDNDLogic() {
	m_dragSourceItemSlot = nullptr;
	m_isDraggingItem = false;
}

bool InventoryUIInteractions::isDraggingItem() {
	return m_isDraggingItem;
}

ItemHandle* InventoryUIInteractions::getDraggedItem() {
	return m_dragSourceItemSlot;
}