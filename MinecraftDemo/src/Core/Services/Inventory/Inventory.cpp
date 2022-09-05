#include "Inventory.h"

Inventory::Inventory(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_itemBarSelectedSlot(0),
	m_inventory(new ItemSlot*[TOTAL_SLOTS]) {
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		m_inventory[i] = new ItemSlot();
	}
	m_itemBar = &m_inventory[TOTAL_SLOTS - ITEMBAR_SLOTS];
}

Inventory::~Inventory() {
	delete[] m_inventory;
}

void Inventory::init(ItemLibrary* itemLibrary) {
	m_itemLibrary = itemLibrary;
}

int Inventory::queryAvailableSpaceForItemId(ItemId itemId) {
	int spaceAvailable = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		if(m_inventory[i] != nullptr && m_inventory[i]->getItem()->getItemId() == itemId) {
			spaceAvailable += (m_inventory[i]->getItem()->getItemMaxStackCount() - m_inventory[i]->getItem()->getItemCount());
		}
	}
	return spaceAvailable;
}

int Inventory::queryItemCount(ItemId itemId) {
	int itemCount = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		Item* item = m_inventory[i]->getItem();
		if (item != nullptr && item->getItemId() == itemId) {
			itemCount += item->getItemCount();
		}
	}
	return itemCount;
}

void Inventory::addItem(ItemId itemId, int count) {
	int itemsLeft = (int)count;
	if (itemsLeft > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			Item* item = m_inventory[i]->getItem();
			if (item != nullptr && item->getItemId() == itemId) {
				int stackSpaceAvailable = item->getItemMaxStackCount() - item->getItemCount();
				item->setItemCount(item->getItemCount() + glm::min(stackSpaceAvailable, itemsLeft));
				itemsLeft -= (item->getItemCount() - (item->getItemMaxStackCount() - stackSpaceAvailable));
			}
		}
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			ItemSlot* itemslot = m_inventory[i];
			if (itemslot->isEmpty()) {
				ItemSpecification* newItemSpec = m_itemLibrary->getItemSpecification(itemId);
				itemslot->replaceItem(new Item(newItemSpec, glm::min(newItemSpec->getItemMaxStackCount(), itemsLeft)));
				itemsLeft -= m_inventory[i]->getItem()->getItemCount();
			}
		}
	}
}

void Inventory::removeItem(ItemId itemId, int count) {
	if (count > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (count > 0); i++) {
			ItemSlot* itemSlot = m_inventory[i];
			if (!itemSlot->isEmpty() && itemSlot->getItem()->getItemId() == itemId) {
				int itemCount = itemSlot->getItem()->getItemCount();
				itemSlot->decreaseItemCountBy(count);
				if (count < itemCount) {
					count = 0;
				}
				else {
					count -= itemCount;
				}
			}
		}
	}
}

void Inventory::addItemInInventorySlot(ItemId itemId, int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		ItemSlot* itemSlot = m_inventory[slot];
		if(itemSlot->isEmpty()) {
			ItemSpecification* newItemSpec = m_itemLibrary->getItemSpecification(itemId);
			itemSlot->replaceItem(new Item(newItemSpec, glm::min(newItemSpec->getItemMaxStackCount(), (int)count)));
		} else if (itemSlot->getItem()->getItemId() == itemId) {
			itemSlot->increaseItemCountBy(count);
		}
	}
}

void Inventory::removeItemInInventorySlot(unsigned int slot) {
	if (slot < TOTAL_SLOTS) {
		m_inventory[slot]->resetItem();
	}
}

Item* Inventory::takeItemFromInventorySlot(unsigned int slot) {
	Item* toTake = nullptr;
	if (slot < TOTAL_SLOTS) {
		ItemSlot* itemSlot = m_inventory[slot];
		if (!itemSlot->isEmpty()) {
			toTake = itemSlot->takeItem();
		}
	}
	return toTake;
}

void Inventory::moveExistingItemInSlot(unsigned int slot, Item* item) {
	if (slot < TOTAL_SLOTS) {
		m_inventory[slot]->replaceItem(item);
	}
}

void Inventory::decreaseItemCountInSlot(int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		ItemSlot* itemSlot = m_inventory[slot];
		if (!itemSlot->isEmpty()) {
			itemSlot->decreaseItemCountBy(count);
		}
	}
}

void Inventory::splitItemSlot(unsigned int slot) {
	if (slot < TOTAL_SLOTS) {
		ItemSlot* itemSlot = m_inventory[slot];
		if (!itemSlot->isEmpty() && itemSlot->getItem()->getItemCount() > 1) {
			for (int i = 0; (i < TOTAL_SLOTS); i++) {
				ItemSlot* currentSlot = m_inventory[i];
				if (currentSlot->isEmpty()) {
					Item* splitItem = itemSlot->getItem()->clone();
					int countHalf = splitItem->getItemCount() / 2;
					itemSlot->decreaseItemCountBy(countHalf);
					splitItem->setItemCount(countHalf);
					currentSlot->replaceItem(splitItem);
					break;
				}
			}
		}
	}
}

ItemSlot** Inventory::getItemBar() {
	return m_itemBar;
}

ItemSlot* Inventory::getItemSlot(unsigned int slot) {
	ItemSlot* itemSlot = nullptr;
	if (slot < TOTAL_SLOTS) {
		itemSlot = m_inventory[slot];
	}
	return itemSlot;
}

Item* Inventory::getSelectedItem() {
	return m_inventory[getInventorySlots() + getItemBarSelectedSlot()]->getItem();
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