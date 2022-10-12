#include "Item.h"

Item::Item() :
	m_itemSharedSpec(nullptr) {

}

Item::~Item() {

}

ImageTexture2D* Item::getItemIcon() {
	return m_itemSharedSpec->getItemIcon();
}

void Item::itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {

}

void Item::itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {

}

void Item::itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {

}

void Item::itemSecondaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {

}

ItemId Item::getItemId() {
	return m_itemSharedSpec->getItemId();
}

float Item::getItemBreakScalingFactor() {
	return m_itemSharedSpec->getItemBreakScalingFactor();
}

int Item::getItemMaxStackCount() {
	return m_itemSharedSpec->getItemMaxStackCount();
}

bool Item::isCompatibleWith(IItem* target) {
	return target != nullptr && target->getItemId() != ItemId::NONE && getItemId() == target->getItemId();
}