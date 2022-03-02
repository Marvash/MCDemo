#include "Biomes/SavanaBiome.h"

SavanaBiome* SavanaBiome::singleton = nullptr;

SavanaBiome* SavanaBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new SavanaBiome();
	}
	return singleton;
}

SavanaBiome::SavanaBiome() : Biome() {

}

void SavanaBiome::loadConfiguration() {
	biomeId = BiomeId::SAVANA;
	name = "Savana";
	minTemp = 0.5f;
	maxTemp = 0.7f;
	minHum = 0.0f;
	maxHum = 0.3f;
	period = 128;
	amplitude = 8.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 5;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 3333;
	hasTrees = true;
	treesXPerlinSeed = 26738291;
	treesYPerlinSeed = 81762401;
	treeGridCellSide = 70;
}