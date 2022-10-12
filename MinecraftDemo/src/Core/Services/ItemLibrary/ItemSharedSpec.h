#pragma once
#include "ItemIdEnum.h"
#include "Core/Textures/ImageTexture2D.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class ItemSharedSpec {

	friend class ItemLibrary;

public:
	ItemSharedSpec();
	ImageTexture2D* getItemIcon();
	virtual void itemPrimaryActionUpdate(CoreServiceLocator* coreServiceLocator);
	virtual void itemPrimaryActionEnd(CoreServiceLocator* coreServiceLocator);
	virtual void itemSecondaryActionUpdate(CoreServiceLocator* coreServiceLocator);
	virtual void itemSecondaryActionEnd(CoreServiceLocator* coreServiceLocator);
	ItemId getItemId();
	float getItemBreakScalingFactor();
	int getItemMaxStackCount();

protected:
	ItemId m_itemId;
	float m_itemBreakScalingFactor;
	ImageTexture2D* m_itemIcon;
	int m_itemMaxStackCount;
};