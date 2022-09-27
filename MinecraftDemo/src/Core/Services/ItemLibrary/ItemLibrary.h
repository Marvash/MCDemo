#pragma once
#include "ItemSharedSpec.h"
#include "Core/Services/BlockLibrary/BlockIdEnum.h"
#include "ItemIdEnum.h"
#include "IconLibrary/IconLibrary.h"
#include "Core/Services/CoreService.h"
#include "PlaceableItemSharedSpec.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/Biome/BiomeLibrary.h"
#include "Core/Services/BlockLibrary/BlockLibrary.h"
#include "Core/Services/Atlas/Atlas.h"
#include <Boost/log/trivial.hpp>

class ItemLibrary {
public:
	ItemLibrary();
	~ItemLibrary();
	void init(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas, BlockLibrary* blockLibrary);
	ItemSharedSpec* getItemSpecification(ItemId itemId);
	PlaceableItemSharedSpec* getPlaceableItemSpecification(ItemId itemId);
private:
	IconLibrary* m_iconLibrary;
	std::map<ItemId, ItemSharedSpec*> m_itemSpecifications;
	std::map<ItemId, PlaceableItemSharedSpec*> m_placeableItemSpecifications;
	void generateItemSpecifications();
	void generatePlaceableItemSpecifications();
};