#pragma once
#include "Core/Services/BlockLibrary/BlockIdEnum.h"

class PlaceableItemSharedSpec {

	friend class ItemLibrary;

public:
	PlaceableItemSharedSpec();
	float getItemPlaceInterval();
	BlockId getBlockId();
private:
	float m_itemPlaceInterval;
	BlockId m_blockId;
};