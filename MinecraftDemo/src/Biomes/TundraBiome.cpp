#include "Biomes/TundraBiome.h"

TundraBiome* TundraBiome::singleton = nullptr;

TundraBiome* TundraBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new TundraBiome();
	}
	return singleton;
}

TundraBiome::TundraBiome() : Biome() {

}

void TundraBiome::loadConfiguration() {
	biomeId = BiomeId::TUNDRA;
	name = "Tundra";
	minTemp = 0.0f;
	maxTemp = 0.3f;
	minHum = 0.0f;
	maxHum = 0.3f;
	period = 256;
	amplitude = 8.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 3;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 1111;
	hasTrees = true;
	treesXPerlinSeed = 46738291;
	treesYPerlinSeed = 81762411;
	treeGridCellSide = 100;
}