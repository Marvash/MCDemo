#pragma once
#include "ItemIdEnum.h"
#include "Core/Textures/ImageTexture2D.h"
#include "ItemHandle.h"
#include "ItemSharedSpec.h"

class IItem {
public:
	virtual ~IItem() {};
	virtual ImageTexture2D* getItemIcon() = 0;
	virtual void itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) = 0;
	virtual void itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) = 0;
	virtual void itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) = 0;
	virtual void itemSecondaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) = 0;
	virtual ItemId getItemId() = 0;
	virtual float getItemBreakScalingFactor() = 0;
	virtual int getItemMaxStackCount() = 0;
	virtual bool isCompatibleWith(IItem* target) = 0;
};