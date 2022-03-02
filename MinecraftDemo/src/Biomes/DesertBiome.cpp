#include "Biomes/DesertBiome.h"

DesertBiome* DesertBiome::singleton = nullptr;

DesertBiome* DesertBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new DesertBiome();
	}
	return singleton;
}

DesertBiome::DesertBiome() : Biome() {

}

void DesertBiome::loadConfiguration() {
	biomeId = BiomeId::DESERT;
	name = "Desert";
	minTemp = 0.7f;
	maxTemp = 1.0f;
	minHum = 0.0f;
	maxHum = 0.3f;
	period = 256;
	amplitude = 8.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 3;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 4444;
}