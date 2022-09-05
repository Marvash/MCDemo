#pragma once
#include "ItemSpecification.h"

class CoreServiceLocator;

class ToolItemSpecification : public ItemSpecification {
public:
	ToolItemSpecification(ItemId itemId, ImageTexture2D* itemIcon);
	void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) override;
	void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) override;
private:
	static const int MAX_TOOL_ITEM_STACK = 1;
};