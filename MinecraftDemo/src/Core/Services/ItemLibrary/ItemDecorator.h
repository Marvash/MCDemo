#pragma once
#include "IItem.h"

class ItemDecorator : public IItem {
public:
	virtual ~ItemDecorator();
	virtual ImageTexture2D* getItemIcon() override;
	virtual void itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemSecondaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual ItemId getItemId() override;
	virtual float getItemBreakScalingFactor() override;
	virtual int getItemMaxStackCount() override;
	virtual bool isCompatibleWith(IItem* target) override;
protected:
	ItemDecorator(IItem* wrappedItem);

	IItem* m_wrappedItem;
};