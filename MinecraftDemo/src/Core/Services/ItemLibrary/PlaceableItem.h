#pragma once
#include "ItemIdEnum.h"
#include "IItem.h"
#include "ItemDecorator.h"
#include "PlaceableItemSharedSpec.h"
#include "Core/Services/BlockLibrary/BlockIdEnum.h"

class CoreServiceLocator;

class PlaceableItem : public ItemDecorator {

	friend class ItemLibrary;
	friend class ItemGenerator;

public:
	virtual void itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) override;
private:
	PlaceableItem(IItem* wrappedItem);

	PlaceableItemSharedSpec* m_placeableItemSharedSpec;
	float m_lastPlacedTime;
};