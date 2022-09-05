#pragma once
#include "ItemSpecification.h"

class CoreServiceLocator;

class DefaultItemSpecification : public ItemSpecification {
public:
	DefaultItemSpecification(ItemId itemId, ImageTexture2D* itemIcon);
	void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) override;
	void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) override;
private:
	static const int MAX_DEFAULT_ITEM_STACK = 64;
};