#pragma once
#include "Core/GameObject/GameObject.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Cube/Cube.h"
#include "Core/TerrainGenerator/TerrainGenerator.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/Atlas/Atlas.h"
#include "BiomeLibrary.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class BiomeService : public CoreService {
public:
	BiomeService(CoreEventDispatcher* coreEventDispatcher);
	void init(BiomeLibrary* biomeLibrary);
	void onNotify(Event& newEvent) override;
	unsigned int getBiomesCount();
	TextureBuffer* getBiomeColorsBuffer();
	int getBiomeCubeColors(Biome::BiomeId biomeId, CubeId cubeId, Cube::FaceSide faceSide);
	Biome** getBiomes();
private:
	BiomeLibrary* m_biomeLibrary;
};