#pragma once
#include "coreInclude.h"
#include "Cube.h"
#include "PerlinNoiseGenerator.h"
#include "Biome.h"

class TerrainGenerator {

public:

	PerlinNoiseGenerator temperaturePerlinGen;
	PerlinNoiseGenerator humidityPerlinGen;

	PerlinNoiseGenerator terrainPerlinGen;

	TerrainGenerator(int chunkSideSize, int chunkHeight);
	void generateChunk(Cube*** &blockMatrix, glm::vec3 &chunkPosition, Chunk* &parentChunk);
	float getHeight(float x, float y);
	int test = 0;

private:

	const float perlinNormFactor = 0.55f; // should be sqrt(1/2), close enough
	const int biomePerlinPeriod = 1024;
	const int biomePerlinLODs = 4;
	const float biomeNeighbourInfluenceThreshold = 0.1f;
	//const int smoothingGridCellSize = 8;

	const float seaLevel = 90;

	int chunkSideSize;
	int chunkHeight;
	int numBiomes;
	Biome* biomes;


	float bilinearFilter(float x, float y, float* samples, float* corners);
	void getBilinearSmoothingGridCoordinates(float x, float y, float* corners, int smoothingGridCellSize = 10);
	void populateBiomesArray();
};

