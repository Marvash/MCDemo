#include "ItemSlot.h"

ItemSlot::ItemSlot() : m_item(nullptr) {

}

ItemSlot::~ItemSlot() {
	resetItem();
}

void ItemSlot::swapItemSlot(ItemSlot* itemSlot) {
	Item* tmp = itemSlot->takeItem();
	itemSlot->replaceItem(m_item);
	m_item = tmp;
}

void ItemSlot::mergeItemSlot(ItemSlot* itemSlot) {
	if (!isEmpty() && m_item->isCompatibleWith(itemSlot->getItem())) {
		int itemCountToMax = m_item->getItemMaxStackCount() - m_item->getItemCount();
		int mergeCountDelta = 0;
		if (itemSlot->getItem()->getItemCount() <= itemCountToMax) {
			mergeCountDelta = itemSlot->getItem()->getItemCount();
		}
		else {
			mergeCountDelta = itemCountToMax;
		}
		increaseItemCountBy(mergeCountDelta);
		itemSlot->decreaseItemCountBy(mergeCountDelta);
	}
}

void ItemSlot::resolveSlotDrag(ItemSlot* itemSlot) {
	if (checkMergeCompatibility(itemSlot)) {
		mergeItemSlot(itemSlot);
	}
	else {
		swapItemSlot(itemSlot);
	}
}

void ItemSlot::decreaseItemCountBy(int count) {
	if (!isEmpty()) {
		m_item->setItemCount(m_item->getItemCount() - count);
		if (m_item->getItemCount() <= 0) {
			delete m_item;
			m_item = nullptr;
		}
	}
}

void ItemSlot::increaseItemCountBy(int count) {
	if (!isEmpty()) {
		m_item->setItemCount(m_item->getItemCount() + count);
	}
}

Item* ItemSlot::getItem() {
	return m_item;
}

Item* ItemSlot::takeItem() {
	Item* toTake = m_item;
	m_item = nullptr;
	return toTake;
}

void ItemSlot::replaceItem(Item* item) {
	resetItem();
	m_item = item;
}

void ItemSlot::resetItem() {
	if (!isEmpty()) {
		delete m_item;
		m_item = nullptr;
	}
}

bool ItemSlot::isEmpty() {
	return m_item == nullptr;
}

bool ItemSlot::checkMergeCompatibility(ItemSlot* itemSlot) {
	return !isEmpty() && m_item->isCompatibleWith(itemSlot->getItem());
}