#pragma once
#include "coreInclude.h"
#include "PerlinNoiseGenerator.h"
#include "Cube.h"

class Biome
{
public:

	enum class BiomeId {
		NONE,
		TUNDRA,
		TAIGA,
		SAVANA,
		DESERT,
		MOUNTAINS,
		HILLS,
		PLAINS,
		FOREST,
		JUNGLE
	};

	BiomeId biomeId;
	std::string name;
	glm::vec3 grassColor;
	float minTemp;
	float maxTemp;
	float minHum;
	float maxHum;
	int period;
	float amplitude;
	float frequency;
	float baseHeight;
	int smoothGridSize;
	int terrainDetailLevels;
	unsigned long long seed;
	bool hasTrees;

	// TODO: MOVE SEA LEVEL INTO WORLD CONFIGURATION
	const float seaLevel = 90.0f;

	virtual float getBlockHeight(float x, float y);

	virtual void loadConfiguration() = 0;
	virtual void initBiome();

protected:
	PerlinNoiseGenerator baseBiomePerlinGen;
	
	Biome();
};

