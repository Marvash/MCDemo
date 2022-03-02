#pragma once
#include "coreInclude.h"
#include "Cube.h"
#include "PerlinNoiseGenerator.h"
#include "Biomes/TundraBiome.h"
#include "Biomes/TaigaBiome.h"
#include "Biomes/MountainsBiome.h"
#include "Biomes/ForestBiome.h"
#include "Biomes/PlainsBiome.h"
#include "Biomes/DesertBiome.h"
#include "Biomes/HillsBiome.h"
#include "Biomes/JungleBiome.h"
#include "Biomes/SavanaBiome.h"
#include "TreeBuilder.h"

class TerrainGenerator {

public:

	static void initBiomesArray();

	static Biome** biomesArray();
	static unsigned int getBiomesCount();

	PerlinNoiseGenerator temperaturePerlinGen;
	PerlinNoiseGenerator humidityPerlinGen;

	TerrainGenerator(int chunkSideSize, int chunkHeight);
	void generateChunk(Cube*** &blockMatrix, glm::vec3 &chunkPosition);
	void decorateChunk(Cube*** &blockMatrix, glm::vec3 &chunkPosition);
	float getHeight(float x, float y);
	int test = 0;

private:

	static Biome** biomes;
	static unsigned int biomesCount;

	const float perlinNormFactor = 0.55f; // should be sqrt(1/2)
	const unsigned int biomePerlinPeriod = 1024;
	const unsigned int biomePerlinLODs = 4;
	const float biomeNeighbourInfluenceThreshold = 0.1f;
	//const int smoothingGridCellSize = 8;

	static const float seaLevel;

	int chunkSideSize;
	int chunkHeight;

	unsigned int treeChunkOffset;

	PerlinNoiseGenerator treesPerlinGen;
	TreeBuilder treeBuilder;

	float bilinearFilter(float x, float y, float* samples, float* corners);
	void getBilinearSmoothingGridCoordinates(float x, float y, float* corners, int smoothingGridCellSize = 10);
	void computeAreaTreeList(float chunkX, float chunkY, unsigned int treeChunkSideSize, std::vector<std::pair<float, float>>& trees, Biome* biome);
	float computeTerrainHeight(float x, float y, Biome*& biome);
};

