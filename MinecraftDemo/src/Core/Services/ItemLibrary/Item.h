#pragma once
#include "Core/Services/ItemLibrary/ItemSpecification.h"
#include <glm/common.hpp>

class Item {
public:
	Item(ItemSpecification* itemSpecification, int count = 1);
	void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator);
	void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator);
	ItemId getItemId();
	int getItemMaxStackCount();
	int getItemCount();
	ImageTexture2D* getItemIcon();
	void setItemCount(int count);
	bool isCompatibleWith(Item* target);
	Item* clone();
private:
	ItemSpecification* m_itemSpecification;
	int m_count;
};