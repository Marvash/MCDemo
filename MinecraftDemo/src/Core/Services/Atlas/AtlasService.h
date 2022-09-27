#pragma once
#include "Core/GameObject/GameObject.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Services/BlockLibrary/Block.h"
#include "Core/TerrainGenerator/TerrainGenerator.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/Atlas/Atlas.h"
#include "Atlas.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class AtlasService : public CoreService {
public:
	AtlasService(CoreEventDispatcher* coreEventDispatcher);
	void init(Atlas* atlas);
	void onNotify(Event& newEvent) override;
	int getBlockTexIndex(BlockId blockId, BlockFace faceSide);
	TextureBuffer* getTexCoordsBuffer();
private:
	Atlas* m_atlas;
};