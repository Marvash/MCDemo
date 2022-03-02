#include "Biomes/HillsBiome.h"

HillsBiome* HillsBiome::singleton = nullptr;

HillsBiome* HillsBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new HillsBiome();
	}
	return singleton;
}

HillsBiome::HillsBiome() : Biome() {

}

void HillsBiome::loadConfiguration() {
	biomeId = BiomeId::HILLS;
	name = "Hills";
	minTemp = 0.5f;
	maxTemp = 0.7f;
	minHum = 0.3f;
	maxHum = 0.5f;
	period = 128;
	amplitude = 30.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 10;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 6666;
	hasTrees = true;
	treesXPerlinSeed = 4687731;
	treesYPerlinSeed = 76621411;
	treeGridCellSide = 8;
}