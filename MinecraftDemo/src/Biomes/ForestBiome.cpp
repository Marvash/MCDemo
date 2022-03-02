#include "Biomes/ForestBiome.h"

ForestBiome* ForestBiome::singleton = nullptr;

ForestBiome* ForestBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new ForestBiome();
	}
	return singleton;
}

ForestBiome::ForestBiome() : Biome() {

}

void ForestBiome::loadConfiguration() {
	biomeId = BiomeId::FOREST;
	name = "Forest";
	minTemp = 0.5f;
	maxTemp = 1.0f;
	minHum = 0.5f;
	maxHum = 0.8f;
	period = 64;
	amplitude = 8.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 8;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 8888;
	hasTrees = true;
	treesXPerlinSeed = 4688831543253;
	treesYPerlinSeed = 76411553252;
	treeGridCellSide = 10;
}

void ForestBiome::initBiome() {
	Biome::initBiome();
	treesXPerlinGen.setSeed(treesXPerlinSeed);
	treesXPerlinGen.setPeriod(1);
	treesYPerlinGen.setSeed(treesYPerlinSeed);
	treesYPerlinGen.setPeriod(1);
}