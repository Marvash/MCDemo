#pragma once
#include "Core/GameObject/GameObject.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Cube/Cube.h"
#include "Core/TerrainGenerator/TerrainGenerator.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/BiomeManager/BiomeManager.h"
#include "BiomeManager.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class BiomeService : public CoreService {
public:
	BiomeService(CoreEventDispatcher* coreEventDispatcher);
	void init(BiomeManager* biomeManager);
	void onNotify(Event& newEvent) override;
	unsigned int getBiomesCount();
	TextureBuffer* getBiomeColorsBuffer();
	int getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide);
	Biome** getBiomes();
private:
	BiomeManager* m_biomeManager;
};