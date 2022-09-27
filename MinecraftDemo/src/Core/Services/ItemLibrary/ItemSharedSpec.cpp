#include "ItemSharedSpec.h"
#include "Core/Services/CoreServiceLocator.h"

ItemSharedSpec::ItemSharedSpec() :
	m_itemId(ItemId::NONE),
	m_itemIcon(nullptr),
	m_itemMaxStackCount(0),
	m_itemBreakScalingFactor(1.0f) {

}

void ItemSharedSpec::itemPrimaryActionUpdate(CoreServiceLocator* coreServiceLocator) {

}

void ItemSharedSpec::itemPrimaryActionEnd(CoreServiceLocator* coreServiceLocator) {

}

void ItemSharedSpec::itemSecondaryActionUpdate(CoreServiceLocator* coreServiceLocator) {

}

void ItemSharedSpec::itemSecondaryActionEnd(CoreServiceLocator* coreServiceLocator) {

}

ItemId ItemSharedSpec::getItemId() {
	return m_itemId;
}

ImageTexture2D* ItemSharedSpec::getItemIcon() {
	return m_itemIcon;
}

float ItemSharedSpec::getItemBreakScalingFactor() {
	return m_itemBreakScalingFactor;
}

int ItemSharedSpec::getItemMaxStackCount() {
	return m_itemMaxStackCount;
}