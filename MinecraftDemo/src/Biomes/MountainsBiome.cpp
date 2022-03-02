#include "Biomes/MountainsBiome.h"

MountainsBiome* MountainsBiome::singleton = nullptr;

MountainsBiome* MountainsBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new MountainsBiome();
	}
	return singleton;
}

MountainsBiome::MountainsBiome() : Biome() {

}

void MountainsBiome::loadConfiguration() {
	biomeId = BiomeId::MOUNTAINS;
	name = "Mountains";
	minTemp = 0.3f;
	maxTemp = 0.5f;
	minHum = 0.3f;
	maxHum = 0.5f;
	period = 128;
	amplitude = 60.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 15;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 5555;
	hasTrees = true;
	treesXPerlinSeed = 44735231;
	treesYPerlinSeed = 21766410;
	treeGridCellSide = 10;
}