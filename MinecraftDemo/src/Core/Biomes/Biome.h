#pragma once
#include "Utils/Random/PerlinGenerator/PerlinNoiseGenerator.h"
#include <glm/glm.hpp>

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

	void initBiome();
	virtual ~Biome();

	BiomeId m_biomeId;
	std::string m_name;
	glm::vec3 m_grassColor;
	float m_minTemp;
	float m_maxTemp;
	float m_minHum;
	float m_maxHum;
	int m_period;
	float m_amplitude;
	float m_frequency;
	float m_baseHeight;
	int m_smoothGridSize;
	int m_terrainDetailLevels;
	unsigned long long m_seed;
	bool m_hasTrees;
	PerlinNoiseGenerator m_baseBiomePerlinGen;

protected:
	Biome();
	
};

