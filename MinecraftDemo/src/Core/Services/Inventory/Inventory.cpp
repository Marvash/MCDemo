#include "Inventory.h"

Inventory::Inventory(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_itemBarSelectedSlot(0),
	m_inventory(new ItemHandle*[TOTAL_SLOTS]) {
	m_itemBar = &m_inventory[TOTAL_SLOTS - ITEMBAR_SLOTS];
}

Inventory::~Inventory() {
	delete[] m_inventory;
}

void Inventory::init(ItemGenerator* itemGenerator) {
	m_itemGenerator = itemGenerator;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		m_inventory[i] = m_itemGenerator->createItemHandle(ItemId::NONE);
	}
}

int Inventory::queryAvailableSpaceForItemId(ItemId itemId) {
	int spaceAvailable = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		if(m_inventory[i] != nullptr && m_inventory[i]->getItemId() == itemId) {
			spaceAvailable += (m_inventory[i]->getItemMaxStackCount() - m_inventory[i]->getItemCount());
		}
	}
	return spaceAvailable;
}

int Inventory::queryItemCount(ItemId itemId) {
	int itemCount = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		ItemHandle* item = m_inventory[i];
		if (item != nullptr && item->getItemId() == itemId) {
			itemCount += item->getItemCount();
		}
	}
	return itemCount;
}

void Inventory::addItem(ItemHandle* itemToAdd) {
	int itemsLeft = itemToAdd->getItemCount();
	if (itemsLeft > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			ItemHandle* item = m_inventory[i];
			if (item->isCompatibleWith(itemToAdd)) {
				itemsLeft -= item->mergeWithHandle(itemToAdd);
			}
		}
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			ItemHandle* item = m_inventory[i];
			if (item->isNullItem()) {
				item->swapHandle(itemToAdd);
				itemsLeft -= item->getItemCount();
			}
		}
	}
}

void Inventory::addItem(ItemId itemId, int count) {
	int itemsLeft = count;
	if (itemsLeft > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			ItemHandle* item = m_inventory[i];
			if (item->getItemId() == itemId) {
				int availableSpace = item->getItemMaxStackCount() - item->getItemCount();
				int toAdd = glm::min(availableSpace, itemsLeft);
				item->addToItemCount(toAdd);
				itemsLeft -= toAdd;
			}
		}
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			ItemHandle* item = m_inventory[i];
			if (item->isNullItem()) {
				m_itemGenerator->changeItemHandle(item, itemId, itemsLeft);
				itemsLeft -= item->getItemCount();
			}
		}
	}
}

void Inventory::addItemInEmptyInventorySlot(ItemId itemId, int count, unsigned int slot) {
	ItemHandle* item = m_inventory[slot];
	if (item->isNullItem() && count > 0) {
		m_itemGenerator->changeItemHandle(item, itemId, count);
	}
}

void Inventory::removeItem(ItemId itemId, int count) {
	if (count > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (count > 0); i++) {
			ItemHandle* item = m_inventory[i];
			if (!item->isNullItem() && item->getItemId() == itemId) {
				int itemCount = item->getItemCount();
				int toSubtract = glm::min(count, itemCount);
				item->subtractToItemCount(toSubtract);
				count -= toSubtract;
			}
		}
	}
}

void Inventory::splitItemInSlot(unsigned int slot) {
	if (slot < TOTAL_SLOTS) {
		ItemHandle* itemToSplit = m_inventory[slot];
		if (!itemToSplit->isNullItem() && itemToSplit->getItemCount() > 1) {
			for (int i = 0; (i < TOTAL_SLOTS); i++) {
				ItemHandle* item = m_inventory[i];
				if (item->isNullItem()) {
					int countHalf = (itemToSplit->getItemCount() / 2);
					m_itemGenerator->changeItemHandle(item, itemToSplit->getItemId(), countHalf);
					itemToSplit->subtractToItemCount(countHalf);
					break;
				}
			}
		}
	}
}

ItemHandle** Inventory::getItemBar() {
	return m_itemBar;
}

ItemHandle* Inventory::getItemInSlot(unsigned int slot) {
	ItemHandle* item = nullptr;
	if (slot < TOTAL_SLOTS) {
		item = m_inventory[slot];
	}
	return item;
}

ItemHandle* Inventory::getSelectedItem() {
	return m_inventory[getInventorySlots() + getItemBarSelectedSlot()];
}

unsigned int Inventory::getItemBarSelectedSlot() {
	return m_itemBarSelectedSlot - getInventorySlots();
}

void Inventory::setItemBarSelectedSlot(unsigned int itemBarSlot) {
	if ((getInventorySlots() + itemBarSlot) < TOTAL_SLOTS) {
		m_itemBarSelectedSlot = getInventorySlots() + itemBarSlot;
	}
}

unsigned int Inventory::getItemBarSelectedSlotAbs() {
	return getInventorySlots() + getItemBarSelectedSlot();
}

unsigned int Inventory::getInventorySlots() {
	return TOTAL_SLOTS - ITEMBAR_SLOTS;
}

void Inventory::onNotify(Event& newEvent) {

}