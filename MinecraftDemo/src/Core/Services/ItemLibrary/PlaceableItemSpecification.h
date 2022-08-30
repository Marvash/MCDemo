#pragma once
#include "ItemSpecification.h"
#include "Core/Cube/CubeIdEnum.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class PlaceableItemSpecification : public ItemSpecification {
public:
	PlaceableItemSpecification(ItemId itemId, ImageTexture2D* itemIcon, CubeId cubeId);
	virtual void performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) override;
	virtual void performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) override;
private:
	static const int MAX_PLACEABLE_ITEM_STACK = 64;

	CubeId m_cubeId;
};