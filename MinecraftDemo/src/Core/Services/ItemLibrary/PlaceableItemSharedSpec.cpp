#include "PlaceableItemSharedSpec.h"

PlaceableItemSharedSpec::PlaceableItemSharedSpec() {

}

float PlaceableItemSharedSpec::getItemPlaceInterval() {
	return m_itemPlaceInterval;
}

BlockId PlaceableItemSharedSpec::getBlockId() {
	return m_blockId;
}