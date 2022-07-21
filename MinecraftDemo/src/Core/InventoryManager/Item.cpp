#include "Item.h"

Item::Item() :
	m_type(ItemType::NONE) {
}

Item::ItemType Item::getItemType() {
	return m_type;
}