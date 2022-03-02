#include "Biomes/PlainsBiome.h"

PlainsBiome* PlainsBiome::singleton = nullptr;

PlainsBiome* PlainsBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new PlainsBiome();
	}
	return singleton;
}

PlainsBiome::PlainsBiome() : Biome() {

}

void PlainsBiome::loadConfiguration() {
	biomeId = BiomeId::PLAINS;
	name = "Plains";
	minTemp = 0.7f;
	maxTemp = 1.0f;
	minHum = 0.3f;
	maxHum = 0.5f;
	period = 128;
	amplitude = 5.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 8;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 7777;
	hasTrees = true;
	treesXPerlinSeed = 46738231;
	treesYPerlinSeed = 81766411;
	treeGridCellSide = 30;
}