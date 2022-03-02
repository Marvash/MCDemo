#include "Biomes/TaigaBiome.h"

TaigaBiome* TaigaBiome::singleton = nullptr;

TaigaBiome* TaigaBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new TaigaBiome();
	}
	return singleton;
}

TaigaBiome::TaigaBiome() : Biome() {

}

void TaigaBiome::loadConfiguration() {
	biomeId = BiomeId::TAIGA;
	name = "Taiga";
	minTemp = 0.3f;
	maxTemp = 0.5f;
	minHum = 0.0f;
	maxHum = 0.3f;
	period = 128;
	amplitude = 8.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 5;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 2222;
	hasTrees = true;
	treesXPerlinSeed = 46738281;
	treesYPerlinSeed = 85762411;
	treeGridCellSide = 6;
}