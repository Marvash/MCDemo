#include "ItemSpecification.h"
#include "Core/Services/CoreServiceLocator.h"

ItemSpecification::ItemSpecification(ItemId itemId, ImageTexture2D* itemIcon, int maxStackCount) :
	m_itemId(itemId),
	m_itemIcon(itemIcon),
	m_itemMaxStackCount(maxStackCount) {

}

ItemId ItemSpecification::getItemId() {
	return m_itemId;
}

ImageTexture2D* ItemSpecification::getItemIcon() {
	return m_itemIcon;
}

int ItemSpecification::getItemMaxStackCount() {
	return m_itemMaxStackCount;
}