#include "InventoryManager.h"

InventoryManager::InventoryManager() :
	m_selectedSlot(0),
	m_itemBar(new Item[ITEMBAR_SLOTS]) {

}

InventoryManager::~InventoryManager() {
	delete[] m_itemBar;
}