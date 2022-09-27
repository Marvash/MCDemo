#pragma once
#include "ItemIdEnum.h"
#include "Core/Textures/ImageTexture2D.h"
#include "ItemIdEnum.h"
#include "ItemSharedSpec.h"
#include "IItem.h"
#include "ItemHandle.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class Item : public IItem {

	friend class ItemLibrary;
	friend class ItemGenerator;

public:
	virtual ~Item();
	virtual ImageTexture2D* getItemIcon() override;
	virtual void itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemSecondaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual ItemId getItemId() override;
	virtual float getItemBreakScalingFactor() override;
	virtual int getItemMaxStackCount() override;
	virtual bool isCompatibleWith(IItem* target) override;
private:
	Item();

	ItemSharedSpec* m_itemSharedSpec;
};
