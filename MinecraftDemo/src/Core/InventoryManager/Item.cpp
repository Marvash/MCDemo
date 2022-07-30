#include "Item.h"

Item::Item(ItemType type, unsigned int count) :
	m_type(type),
	m_count(count) {

}

Item::ItemType Item::getItemType() {
	return m_type;
}

unsigned int Item::getCount() {
	return m_count;
}

void Item::setCount(unsigned int count) {
	m_count = count;
}