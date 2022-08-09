#pragma once
#include "Core/Biomes/TundraBiome.h"
#include "Core/Biomes/TaigaBiome.h"
#include "Core/Biomes/MountainsBiome.h"
#include "Core/Biomes/ForestBiome.h"
#include "Core/Biomes/PlainsBiome.h"
#include "Core/Biomes/DesertBiome.h"
#include "Core/Biomes/HillsBiome.h"
#include "Core/Biomes/JungleBiome.h"
#include "Core/Biomes/SavanaBiome.h"
#include "Core/Biomes/BiomeBuilder.h"
#include "Core/Biomes/BiomeColors.h"
#include "Core/Cube/Cube.h"
#include "Core/Textures/TextureBuffer.h"
#include "Core/Services/CoreService.h"
#include "Core/CoreEventDispatcher.h"
#include <vector>

class BiomeManager : public CoreService {
public:
	BiomeManager(CoreEventDispatcher* coreEventDispatcher);
	
	unsigned int getBiomesCount();
	TextureBuffer* getBiomeColorsBuffer();
	int getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide);
	Biome** getBiomes();
	void init();
	void onNotify(Event& newEvent) override;
	void notify(Event& newEvent) override;

	const unsigned int SEA_LEVEL = 90;
private:
	void initBiomesArray();

	Biome** m_biomes;
	unsigned int m_biomesCount;
	BiomeColors m_biomeColors;
	TextureBuffer* m_biomeColorsBuffer;
};