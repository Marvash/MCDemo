#include "Item.h"

Item::Item(ItemSpecification* itemSpecification, int count) :
	m_itemSpecification(itemSpecification),
	m_count(count) {

}

void Item::performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) {
	m_itemSpecification->performItemPrimaryAction(coreServiceLocator);
}

void Item::performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) {
	m_itemSpecification->performItemSecondaryAction(coreServiceLocator);
}

ItemId Item::getItemId() {
	return m_itemSpecification->getItemId();
}

int Item::getItemCount() {
	return m_count;
}

void Item::setItemCount(int count) {
	m_count = glm::max(glm::min(count, m_itemSpecification->getItemMaxStackCount()), 0);
}

bool Item::isCompatibleWith(Item* target) {
	return target != nullptr && getItemId() == target->getItemId();
}

int Item::getItemMaxStackCount() {
	return m_itemSpecification->getItemMaxStackCount();
}

ImageTexture2D* Item::getItemIcon() {
	return m_itemSpecification->getItemIcon();
}

Item* Item::clone() {
	return new Item(m_itemSpecification, m_count);
}