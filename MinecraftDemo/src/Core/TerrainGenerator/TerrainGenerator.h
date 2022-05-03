#pragma once
#include "Core/Cube/Cube.h"
#include "Utils/Random/PerlinGenerator/PerlinNoiseGenerator.h"
#include "Core/Biomes/TundraBiome.h"
#include "Core/Biomes/TaigaBiome.h"
#include "Core/Biomes/MountainsBiome.h"
#include "Core/Biomes/ForestBiome.h"
#include "Core/Biomes/PlainsBiome.h"
#include "Core/Biomes/DesertBiome.h"
#include "Core/Biomes/HillsBiome.h"
#include "Core/Biomes/JungleBiome.h"
#include "Core/Biomes/SavanaBiome.h"
#include "Core/Services/BiomeManager/BiomeManager.h"
#include "TreeBuilder.h"

class TerrainGenerator {

public:

	PerlinNoiseGenerator m_temperaturePerlinGen;
	PerlinNoiseGenerator m_humidityPerlinGen;

	TerrainGenerator(BiomeManager* biomeManager, int chunkSideSize, int chunkHeight);
	void generateChunk(Cube*** &blockMatrix, glm::vec3 &chunkPosition);
	void decorateChunk(Cube*** &blockMatrix, glm::vec3 &chunkPosition);
	float getDebugHeight(float x, float y);

private:

	const float PERLIN_NORM_FACTOR = 0.55f; // should be sqrt(1/2)
	const unsigned int BIOME_PERLIN_PERIOD = 1024;
	const unsigned int BIOME_PERLIN_LODS = 4;
	const float BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD = 0.1f;
	//const int smoothingGridCellSize = 8;

	const unsigned long long m_temperatureSeed = 1234567;
	const unsigned long long m_humiditySeed = 7654321;

	int m_chunkSideSize;
	int m_chunkHeight;

	unsigned int m_treeChunkOffset;

	TreeBuilder m_treeBuilder;
	BiomeManager* m_biomeManager;

	float getBlockHeight(Biome* biome, float x, float y);
	float bilinearFilter(float x, float y, float* samples, float* corners);
	void getBilinearSmoothingGridCoordinates(float x, float y, float* corners, int smoothingGridCellSize = 10);
	void computeAreaTreeList(float chunkX, float chunkY, unsigned int treeChunkSideSize, std::vector<std::pair<float, float>>& trees, Biome* biome);
	float computeTerrainHeight(float x, float y, Biome*& biome);
};

