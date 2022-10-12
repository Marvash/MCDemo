#include "DroppableBlockSharedSpec.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Inventory/Inventory.h"

DroppableBlockSharedSpec::DroppableBlockSharedSpec() :
	m_droppedCount(0),
	m_coreServiceLocator(nullptr) {

}

int DroppableBlockSharedSpec::getDroppedCount() {
	return m_droppedCount;
}

Inventory* DroppableBlockSharedSpec::getInventory() {
	return m_coreServiceLocator->getInventory();
}

ItemId DroppableBlockSharedSpec::getDroppedItem() {
	return m_droppedItem;
}

bool DroppableBlockSharedSpec::canBeDroppedByItem(ItemId itemUsed) {
	bool shouldDrop = true;
	if (!m_exclusiveItemDropList.empty()) {
		shouldDrop = false;
		for (int i = 0; (i < m_exclusiveItemDropList.size()) && !shouldDrop; i++) {
			if (m_exclusiveItemDropList.at(i) == itemUsed) {
				shouldDrop = true;
			}
		}
	}
	return shouldDrop;
}

void DroppableBlockSharedSpec::dropBlock(ItemHandle* itemUsed, Block* toBreak) {
	Inventory* inventory = m_coreServiceLocator->getInventory();
	if (canBeDroppedByItem(itemUsed->getItemId())) {
		inventory->addItem(m_droppedItem, m_droppedCount);
	}
}