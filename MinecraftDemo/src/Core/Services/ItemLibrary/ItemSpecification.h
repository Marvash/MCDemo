#pragma once
#include "ItemIdEnum.h"
#include "Core/Textures/ImageTexture2D.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class ItemSpecification {
public:
	ItemSpecification(ItemId itemId, ImageTexture2D* itemIcon, int maxStackCount);
	ImageTexture2D* getItemIcon();
	virtual void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) = 0;
	virtual void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) = 0;
	ItemId getItemId();
	int getItemMaxStackCount();

protected:
	ItemId m_itemId;
	ImageTexture2D* m_itemIcon;
	int m_itemMaxStackCount;
};