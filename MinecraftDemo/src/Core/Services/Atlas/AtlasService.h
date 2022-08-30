#pragma once
#include "Core/GameObject/GameObject.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Cube/Cube.h"
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
	int getAtlasTexIndex(CubeId cubeId, Cube::FaceSide faceSide);
	AtlasTexture* getAtlasTexture();
	TextureBuffer* getTexCoordsBuffer();
private:
	Atlas* m_atlas;
};