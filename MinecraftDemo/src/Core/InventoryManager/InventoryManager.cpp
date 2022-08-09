#include "InventoryManager.h"

InventoryManager::InventoryManager() :
	m_itemBarSelectedSlot(0),
	m_inventory(new Item*[TOTAL_SLOTS]) {
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		m_inventory[i] = nullptr;
	}
	m_itemBar = &m_inventory[TOTAL_SLOTS - ITEMBAR_SLOTS];
}

InventoryManager::~InventoryManager() {
	delete[] m_inventory;
}

int InventoryManager::queryItemSpace(Cube::CubeId cubeId) {
	int spaceAvailable = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		if (m_inventory[i] == nullptr) {
			spaceAvailable += MAX_ITEM_STACK;
		} else if(m_inventory[i]->getItemType() == Item::ItemType::CUBE) {
			CubeItem* item = static_cast<CubeItem*>(m_inventory[i]);
			if (item->getCubeId() == cubeId) {
				spaceAvailable += (MAX_ITEM_STACK - item->getCount());
			}
		}
	}
	return spaceAvailable;
}

int InventoryManager::queryItem(Cube::CubeId cubeId) {
	int itemCount = 0;
	for (int i = 0; i < TOTAL_SLOTS; i++) {
		if (m_inventory[i] != nullptr && m_inventory[i]->getItemType() == Item::ItemType::CUBE) {
			CubeItem* item = static_cast<CubeItem*>(m_inventory[i]);
			if (item->getCubeId() == cubeId) {
				itemCount += item->getCount();
			}
		}
	}
	return itemCount;
}

void InventoryManager::addItem(Cube::CubeId cubeId, unsigned int count) {
	int itemsLeft = (int)count;
	if (itemsLeft > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			if (m_inventory[i] != nullptr && m_inventory[i]->getItemType() == Item::ItemType::CUBE) {
				CubeItem* item = static_cast<CubeItem*>(m_inventory[i]);
				if (item->getCubeId() == cubeId) {
					unsigned int stackSpaceAvailable = MAX_ITEM_STACK - item->getCount();
					item->setCount(item->getCount() + glm::min(stackSpaceAvailable, (unsigned int)itemsLeft));
					itemsLeft -= (item->getCount() - (MAX_ITEM_STACK - stackSpaceAvailable));
				}
			}
		}
		for (int i = 0; (i < TOTAL_SLOTS) && (itemsLeft > 0); i++) {
			if (m_inventory[i] == nullptr) {
				m_inventory[i] = new CubeItem(cubeId, glm::min(MAX_ITEM_STACK, (unsigned int)itemsLeft));
				itemsLeft -= m_inventory[i]->getCount();
			}
		}
	}
}

void InventoryManager::removeItem(Cube::CubeId cubeId, unsigned int count) {
	if (count > 0) {
		for (int i = 0; (i < TOTAL_SLOTS) && (count > 0); i++) {
			if (m_inventory[i] != nullptr && m_inventory[i]->getItemType() == Item::ItemType::CUBE) {
				CubeItem* item = static_cast<CubeItem*>(m_inventory[i]);
				if (item->getCubeId() == cubeId) {
					unsigned int itemCount = item->getCount();
					if (count < itemCount) {
						item->setCount(itemCount - count);
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
}

void InventoryManager::addItemInInventorySlot(Cube::CubeId cubeId, unsigned int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		if(m_inventory[slot] == nullptr) {
			m_inventory[slot] = new CubeItem(cubeId, glm::min(MAX_ITEM_STACK, count));
		} else if (m_inventory[slot] != nullptr && m_inventory[slot]->getItemType() == Item::ItemType::CUBE) {
			CubeItem* item = static_cast<CubeItem*>(m_inventory[slot]);
			if (item->getCubeId() == cubeId) {
				unsigned int totalCount = item->getCount() + count;
				item->setCount(glm::min(MAX_ITEM_STACK, totalCount));
			}
		}
	}
}

void InventoryManager::removeItemInInventorySlotCount(Cube::CubeId cubeId, unsigned int count, unsigned int slot) {
	if (count > 0 && slot < TOTAL_SLOTS) {
		if (m_inventory[slot] != nullptr && m_inventory[slot]->getItemType() == Item::ItemType::CUBE) {
			CubeItem* item = static_cast<CubeItem*>(m_inventory[slot]);
			if (item->getCubeId() == cubeId) {
				unsigned int itemCount = item->getCount();
				if (count < itemCount) {
					item->setCount(itemCount - count);
				}
				else {
					delete item;
					m_inventory[slot] = nullptr;
				}
			}
		}
	}
}

void InventoryManager::removeItemInInventorySlot(unsigned int slot) {
	if (slot < TOTAL_SLOTS) {
		if (m_inventory[slot] != nullptr) {
			Item* item = m_inventory[slot];
			delete item;
			m_inventory[slot] = nullptr;
		}
	}
}

void InventoryManager::swapItems(unsigned int source, unsigned int destination) {
	Item* tmp = m_inventory[destination];
	m_inventory[destination] = m_inventory[source];
	m_inventory[source] = tmp;
}

bool InventoryManager::isItemCompatible(Item* source, Item* target) {
	bool compatible = false;
	if (source != nullptr && target != nullptr && source->getItemType() == target->getItemType()) {
		switch (source->getItemType()) {
		case Item::ItemType::CUBE: {
			CubeItem* sourceCubeItem = static_cast<CubeItem*>(source);
			CubeItem* targetCubeItem = static_cast<CubeItem*>(target);
			if (sourceCubeItem->getCubeId() == targetCubeItem->getCubeId()) {
				compatible = true;
			}
			break;
		}
		}
	}
	return compatible;
}

Item** InventoryManager::getItemBar() {
	return m_itemBar;
}

Item* InventoryManager::getItemInSlot(unsigned int slot) {
	Item* item = nullptr;
	if (slot < TOTAL_SLOTS) {
		item = m_inventory[slot];
	}
	return item;
}

Item* InventoryManager::getSelectedItem() {
	return m_inventory[getInventorySlots() + getItemBarSelectedSlot()];
}

unsigned int InventoryManager::getItemBarSelectedSlot() {
	return m_itemBarSelectedSlot - getInventorySlots();
}

void InventoryManager::setItemBarSelectedSlot(unsigned int itemBarSlot) {
	if ((getInventorySlots() + itemBarSlot) < TOTAL_SLOTS) {
		m_itemBarSelectedSlot = getInventorySlots() + itemBarSlot;
	}
}

unsigned int InventoryManager::getItemBarSelectedSlotAbs() {
	return getInventorySlots() + getItemBarSelectedSlot();
}

unsigned int InventoryManager::getInventorySlots() {
	return TOTAL_SLOTS - ITEMBAR_SLOTS;
}