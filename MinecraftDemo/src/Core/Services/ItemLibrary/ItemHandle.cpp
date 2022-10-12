#include "ItemHandle.h"
#include "IItem.h"
#include "Core/Services/CoreServiceLocator.h"
#include "ItemGenerator.h"

ItemGenerator* ItemHandle::m_itemGenerator;

ItemHandle::ItemHandle() :
	m_wrappedItem(nullptr),
	m_nullItem(nullptr),
	m_itemCount(0)
{

}

ItemHandle::~ItemHandle() {
	deleteCurrentWrappedItem();
}

ImageTexture2D* ItemHandle::getItemIcon() {
	return m_wrappedItem->getItemIcon();
}

void ItemHandle::itemPrimaryActionUpdate(CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemPrimaryActionUpdate(this, coreServiceLocator);
}

void ItemHandle::itemPrimaryActionEnd(CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemPrimaryActionEnd(this, coreServiceLocator);

}

void ItemHandle::itemSecondaryActionUpdate(CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemSecondaryActionUpdate(this, coreServiceLocator);

}

void ItemHandle::itemSecondaryActionEnd(CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemSecondaryActionEnd(this, coreServiceLocator);

}

ItemId ItemHandle::getItemId() {
	return m_wrappedItem->getItemId();
}

float ItemHandle::getItemBreakScalingFactor() {
	return m_wrappedItem->getItemBreakScalingFactor();
}

int ItemHandle::getItemMaxStackCount() {
	return m_wrappedItem->getItemMaxStackCount();
}

int ItemHandle::getItemCount() {
	return m_itemCount;
}

void ItemHandle::addToItemCount(unsigned int value) {
	m_itemCount += static_cast<int>(value);;
	int maxStackCount = getItemMaxStackCount();
	if (m_itemCount > maxStackCount) {
		m_itemCount = maxStackCount;
	}
}

void ItemHandle::subtractToItemCount(unsigned int value) {
	m_itemCount -= static_cast<int>(value);
	if (m_itemCount <= 0) {
		m_itemCount = 0;
		deleteCurrentWrappedItem();
		m_wrappedItem = m_nullItem;
	}
}

void ItemHandle::setNull() {
	if (!isNullItem()) {
		subtractToItemCount(m_itemCount);
	}
}

bool ItemHandle::isNullItem() {
	return m_wrappedItem == m_nullItem;
}

bool ItemHandle::isCompatibleWith(ItemHandle* target) {
	return m_wrappedItem->isCompatibleWith(target->m_wrappedItem);
}

void ItemHandle::setWrappedItemInstance(IItem* wrappedItem, unsigned int count) {
	if (wrappedItem != nullptr && count > 0) {
		m_itemCount = 0;
		m_wrappedItem = wrappedItem;
		addToItemCount(count);
	}
}

void ItemHandle::setNullItemInstance(IItem* nullItem) {
	m_nullItem = nullItem;
	m_itemCount = 0;
	if (m_wrappedItem == nullptr) {
		m_wrappedItem = m_nullItem;
	}
}

void ItemHandle::deleteCurrentWrappedItem() {
	if (!isNullItem() && m_wrappedItem != nullptr) {
		delete m_wrappedItem;
	}
}

void ItemHandle::swapHandle(ItemHandle* item) {
	IItem* tmp = item->m_wrappedItem;
	int tmpCount = item->getItemCount();
	item->m_wrappedItem = m_wrappedItem;
	item->m_itemCount = m_itemCount;
	m_wrappedItem = tmp;
	m_itemCount = tmpCount;
}

int ItemHandle::mergeWithHandle(ItemHandle* item) {
	int countToMerge = 0;
	if (isCompatibleWith(item)) {
		int availableSpace = getItemMaxStackCount() - m_itemCount;
		countToMerge = glm::min(availableSpace, item->m_itemCount);
		addToItemCount(countToMerge);
		item->subtractToItemCount(countToMerge);
	}
	return countToMerge;
}

void ItemHandle::changeItem(ItemId itemId, unsigned int count) {
	 m_itemGenerator->changeItemHandle(this, itemId, count);
}