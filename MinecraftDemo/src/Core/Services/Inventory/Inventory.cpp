#include "Inventory.h"

Inventory::Inventory(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_itemBarSelectedSlot(0),
	m_inventory(new Item*[TOTAL_SLOTS]) {
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		m_inventory[i] = nullptr;
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
		if(m_inventory[i] != nullptr && m_inventory[i]->getItemId() == itemId) {
			spaceAvailable += (m_inventory[i]->getItemMaxStackCount() - m_inventory[i]->getItemCount());
		}
	}
	return spaceAvailable;
}

int Inventory::queryItemCount(ItemId itemId) {
	int itemCount = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		Item*& item = m_inventory[i];
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
			Item*& item = m_inventory[i];
			if (item != nullptr && item->getItemId() == itemId) {
				int stackSpaceAvailable = item->getItemMaxStackCount() - item->getItemCount();
				item->setItemCount(item->getItemCount() + glm::min(stackSpaceAvailable, itemsLeft));
				itemsLeft -= (item->getItemCount() - (item->getItemMaxStackCount() - stackSpaceAvailable));
			}
		}
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			Item*& item = m_inventory[i];
			if (item == nullptr) {
				ItemSpecification* newItemSpec = m_itemLibrary->getItemSpecification(itemId);
				item = new Item(newItemSpec, glm::min(newItemSpec->getItemMaxStackCount(), itemsLeft));
				itemsLeft -= m_inventory[i]->getItemCount();
			}
		}
	}
}

void Inventory::removeItem(ItemId itemId, int count) {
	if (count > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (count > 0); i++) {
			if (m_inventory[i] != nullptr && m_inventory[i]->getItemId() == itemId) {
				Item*& item = m_inventory[i];
				int itemCount = item->getItemCount();
				if (count < itemCount) {
					item->setItemCount(itemCount - count);
					count = 0;
				}
				else {
					delete item;
					m_inventory[i] = nullptr;
					count -= itemCount;
				}
			}
		}
	}
}

void Inventory::addItemInInventorySlot(ItemId itemId, int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		Item*& item = m_inventory[slot];
		if(item == nullptr) {
			ItemSpecification* newItemSpec = m_itemLibrary->getItemSpecification(itemId);
			item = new Item(newItemSpec, glm::min(newItemSpec->getItemMaxStackCount(), (int)count));
		} else if (item->getItemId() == itemId) {
			int totalCount = item->getItemCount() + count;
			item->setItemCount(totalCount);
		}
	}
}

void Inventory::removeItemInInventorySlot(unsigned int slot) {
	if (slot < TOTAL_SLOTS) {
		Item*& item = m_inventory[slot];
		if (item != nullptr) {
			delete item;
			item = nullptr;
		}
	}
}

void Inventory::decreaseItemCountInSlot(int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		Item*& item = m_inventory[slot];
		if (item != nullptr) {
			int itemCount = item->getItemCount();
			if (count < itemCount) {
				item->setItemCount(itemCount - count);
			}
			else {
				delete item;
				item = nullptr;
			}
		}
	}
}

void Inventory::swapItems(unsigned int source, unsigned int destination) {
	Item* tmp = m_inventory[destination];
	m_inventory[destination] = m_inventory[source];
	m_inventory[source] = tmp;
}

bool Inventory::isItemCompatible(Item* source, Item* target) {
	return source != nullptr && target != nullptr && source->getItemId() == target->getItemId();
}


Item** Inventory::getItemBar() {
	return m_itemBar;
}

Item* Inventory::getItemInSlot(unsigned int slot) {
	Item* item = nullptr;
	if (slot < TOTAL_SLOTS) {
		item = m_inventory[slot];
	}
	return item;
}

Item* Inventory::getSelectedItem() {
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