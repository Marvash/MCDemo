#pragma once
#include "coreInclude.h"

class Biome
{
public:
	enum class BiomeID {
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

	BiomeID biomeId;
	std::string name;
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

	Biome();
};

