#pragma once
#include "ItemSpecification.h"
#include "Core/Cube/Cube.h"
#include "ItemIdEnum.h"
#include "IconLibrary/IconLibrary.h"
#include "Core/Services/CoreService.h"
#include "PlaceableItemSpecification.h"
#include "NullItemSpecification.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/Biome/BiomeLibrary.h"
#include "Core/Services/Atlas/Atlas.h"
#include <Boost/log/trivial.hpp>

class ItemLibrary : public CoreService {
public:
	ItemLibrary(CoreEventDispatcher* coreEventDispatcher);
	~ItemLibrary();
	void init(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas);
	void onNotify(Event& newEvent) override;
	ItemSpecification* getItemSpecification(ItemId itemId);
private:
	IconLibrary* m_iconLibrary;
	std::map<ItemId, ItemSpecification*> m_itemSpecifications;
	void generateItemSpecifications();
};