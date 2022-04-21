#pragma once
#include "Core/Game/Biomes/TundraBiome.h"
#include "Core/Game/Biomes/TaigaBiome.h"
#include "Core/Game/Biomes/MountainsBiome.h"
#include "Core/Game/Biomes/ForestBiome.h"
#include "Core/Game/Biomes/PlainsBiome.h"
#include "Core/Game/Biomes/DesertBiome.h"
#include "Core/Game/Biomes/HillsBiome.h"
#include "Core/Game/Biomes/JungleBiome.h"
#include "Core/Game/Biomes/SavanaBiome.h"
#include "Core/Game/Biomes/BiomeBuilder.h"
#include "Core/Game/Biomes/BiomeColors.h"
#include "Core/Game/Cube/Cube.h"
#include "Core/Textures/TextureBuffer.h"
#include <vector>

class BiomeManager {
public:
	BiomeManager();
	void initBiomesArray();

	unsigned int getBiomesCount();
	TextureBuffer* getBiomeColorsBuffer();
	int getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide);
	Biome** getBiomes();

	const unsigned int SEA_LEVEL = 90;
private:
	Biome** m_biomes;
	unsigned int m_biomesCount;
	BiomeColors m_biomeColors;
	TextureBuffer* m_biomeColorsBuffer;
};