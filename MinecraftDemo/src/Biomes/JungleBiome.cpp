#include "Biomes/JungleBiome.h"

JungleBiome* JungleBiome::singleton = nullptr;

JungleBiome* JungleBiome::instance()
{
	if (singleton == nullptr) {
		singleton = new JungleBiome();
	}
	return singleton;
}

JungleBiome::JungleBiome() : Biome() {

}

void JungleBiome::loadConfiguration() {
	biomeId = BiomeId::JUNGLE;
	name = "Jungle";
	minTemp = 0.8f;
	maxTemp = 1.0f;
	minHum = 0.8f;
	maxHum = 1.0f;
	period = 64;
	amplitude = 12.0f;
	frequency = 1.0f;
	baseHeight = seaLevel + 10;
	smoothGridSize = 8;
	terrainDetailLevels = 4;
	seed = 9999;
	hasTrees = true;
	treesXPerlinSeed = 467387731;
	treesYPerlinSeed = 8176621411;
	treeGridCellSide = 6;
}