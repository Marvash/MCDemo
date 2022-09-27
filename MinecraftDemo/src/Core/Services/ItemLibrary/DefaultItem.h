#pragma once
#include "ItemIdEnum.h"
#include "IItem.h"
#include "ItemDecorator.h"
#include "Core/Services/BlockLibrary/BlockIdEnum.h"

class CoreServiceLocator;

class DefaultItem : public ItemDecorator {

	friend class ItemLibrary;
	friend class ItemGenerator;

public:
	virtual void itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
	virtual void itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
private:
	DefaultItem(IItem* wrappedItem);
};