#pragma once
#include "ItemSpecification.h"

class NullItemSpecification : public ItemSpecification {
public:
	NullItemSpecification(ItemId itemId, ImageTexture2D* itemIcon);
	void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) override;
	void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) override;
};