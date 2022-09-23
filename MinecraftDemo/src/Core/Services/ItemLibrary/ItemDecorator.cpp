#include "ItemDecorator.h"

ItemDecorator::ItemDecorator(IItem* wrappedItem) : m_wrappedItem(wrappedItem) {

}

ItemDecorator::~ItemDecorator() {

}

ImageTexture2D* ItemDecorator::getItemIcon() {
	return m_wrappedItem->getItemIcon();
}

void ItemDecorator::itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemPrimaryActionUpdate(item, coreServiceLocator);
}

void ItemDecorator::itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemPrimaryActionEnd(item, coreServiceLocator);

}

void ItemDecorator::itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemSecondaryActionUpdate(item, coreServiceLocator);

}

void ItemDecorator::itemSecondaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	m_wrappedItem->itemSecondaryActionEnd(item, coreServiceLocator);
}

ItemId ItemDecorator::getItemId() {
	return m_wrappedItem->getItemId();
}

float ItemDecorator::getItemBreakScalingFactor() {
	return m_wrappedItem->getItemBreakScalingFactor();
}

int ItemDecorator::getItemMaxStackCount() {
	return m_wrappedItem->getItemMaxStackCount();
}

bool ItemDecorator::isCompatibleWith(IItem* target) {
	return m_wrappedItem->isCompatibleWith(target);
}