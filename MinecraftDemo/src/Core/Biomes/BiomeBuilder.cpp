#include "BiomeBuilder.h"

BiomeBuilder::BiomeBuilder(const unsigned int& seaLevel) : SpecializedBuilder<Biome>(), m_seaLevel(seaLevel) {

}

void BiomeBuilder::loadDesertBiome() {
	DesertBiome* desertBiome = new DesertBiome();
	desertBiome->m_biomeId = Biome::BiomeId::DESERT;
	desertBiome->m_name = "Desert";
	desertBiome->m_minTemp = 0.7f;
	desertBiome->m_maxTemp = 1.0f;
	desertBiome->m_minHum = 0.0f;
	desertBiome->m_maxHum = 0.3f;
	desertBiome->m_period = 256;
	desertBiome->m_amplitude = 8.0f;
	desertBiome->m_frequency = 1.0f;
	desertBiome->m_baseHeight = m_seaLevel + 3;
	desertBiome->m_smoothGridSize = 8;
	desertBiome->m_terrainDetailLevels = 4;
	desertBiome->m_seed = 4444;
	desertBiome->m_hasTrees = true;
	desertBiome->initBiome();
	m_result = desertBiome;
}

void BiomeBuilder::loadForestBiome() {
	ForestBiome* forestBiome = new ForestBiome();
	forestBiome->m_biomeId = Biome::BiomeId::FOREST;
	forestBiome->m_name = "Forest";
	forestBiome->m_minTemp = 0.5f;
	forestBiome->m_maxTemp = 1.0f;
	forestBiome->m_minHum = 0.5f;
	forestBiome->m_maxHum = 0.8f;
	forestBiome->m_period = 64;
	forestBiome->m_amplitude = 8.0f;
	forestBiome->m_frequency = 1.0f;
	forestBiome->m_baseHeight = m_seaLevel + 8;
	forestBiome->m_smoothGridSize = 8;
	forestBiome->m_terrainDetailLevels = 4;
	forestBiome->m_seed = 8888;
	forestBiome->m_hasTrees = true;
	forestBiome->m_treesXPerlinSeed = 4688831543253;
	forestBiome->m_treesYPerlinSeed = 76411553252;
	forestBiome->m_treeGridCellSide = 10;
	forestBiome->initBiome();
	m_result = forestBiome;
}

void BiomeBuilder::loadHillsBiome() {
	HillsBiome* hillsBiome = new HillsBiome();
	hillsBiome->m_biomeId = Biome::BiomeId::HILLS;
	hillsBiome->m_name = "Hills";
	hillsBiome->m_minTemp = 0.5f;
	hillsBiome->m_maxTemp = 0.7f;
	hillsBiome->m_minHum = 0.3f;
	hillsBiome->m_maxHum = 0.5f;
	hillsBiome->m_period = 128;
	hillsBiome->m_amplitude = 30.0f;
	hillsBiome->m_frequency = 1.0f;
	hillsBiome->m_baseHeight = m_seaLevel + 10;
	hillsBiome->m_smoothGridSize = 8;
	hillsBiome->m_terrainDetailLevels = 4;
	hillsBiome->m_seed = 6666;
	hillsBiome->m_hasTrees = true;
	hillsBiome->m_treesXPerlinSeed = 4687731;
	hillsBiome->m_treesYPerlinSeed = 76621411;
	hillsBiome->m_treeGridCellSide = 8;
	hillsBiome->initBiome();
	m_result = hillsBiome;
}

void BiomeBuilder::loadJungleBiome() {
	JungleBiome* jungleBiome = new JungleBiome();
	jungleBiome->m_biomeId = Biome::BiomeId::JUNGLE;
	jungleBiome->m_name = "Jungle";
	jungleBiome->m_minTemp = 0.8f;
	jungleBiome->m_maxTemp = 1.0f;
	jungleBiome->m_minHum = 0.8f;
	jungleBiome->m_maxHum = 1.0f;
	jungleBiome->m_period = 64;
	jungleBiome->m_amplitude = 12.0f;
	jungleBiome->m_frequency = 1.0f;
	jungleBiome->m_baseHeight = m_seaLevel + 10;
	jungleBiome->m_smoothGridSize = 8;
	jungleBiome->m_terrainDetailLevels = 4;
	jungleBiome->m_seed = 9999;
	jungleBiome->m_hasTrees = true;
	jungleBiome->m_treesXPerlinSeed = 467387731;
	jungleBiome->m_treesYPerlinSeed = 8176621411;
	jungleBiome->m_treeGridCellSide = 6;
	jungleBiome->initBiome();
	m_result = jungleBiome;
}

void BiomeBuilder::loadMountainsBiome() {
	MountainsBiome* mountainsBiome = new MountainsBiome();
	mountainsBiome->m_biomeId = Biome::BiomeId::MOUNTAINS;
	mountainsBiome->m_name = "Mountains";
	mountainsBiome->m_minTemp = 0.3f;
	mountainsBiome->m_maxTemp = 0.5f;
	mountainsBiome->m_minHum = 0.3f;
	mountainsBiome->m_maxHum = 0.5f;
	mountainsBiome->m_period = 128;
	mountainsBiome->m_amplitude = 60.0f;
	mountainsBiome->m_frequency = 1.0f;
	mountainsBiome->m_baseHeight = m_seaLevel + 15;
	mountainsBiome->m_smoothGridSize = 8;
	mountainsBiome->m_terrainDetailLevels = 4;
	mountainsBiome->m_seed = 5555;
	mountainsBiome->m_hasTrees = true;
	mountainsBiome->m_treesXPerlinSeed = 44735231;
	mountainsBiome->m_treesYPerlinSeed = 21766410;
	mountainsBiome->m_treeGridCellSide = 10;
	mountainsBiome->initBiome();
	m_result = mountainsBiome;
}

void BiomeBuilder::loadPlainsBiome() {
	PlainsBiome* plainsBiome = new PlainsBiome();
	plainsBiome->m_biomeId = Biome::BiomeId::PLAINS;
	plainsBiome->m_name = "Plains";
	plainsBiome->m_minTemp = 0.7f;
	plainsBiome->m_maxTemp = 1.0f;
	plainsBiome->m_minHum = 0.3f;
	plainsBiome->m_maxHum = 0.5f;
	plainsBiome->m_period = 128;
	plainsBiome->m_amplitude = 5.0f;
	plainsBiome->m_frequency = 1.0f;
	plainsBiome->m_baseHeight = m_seaLevel + 8;
	plainsBiome->m_smoothGridSize = 8;
	plainsBiome->m_terrainDetailLevels = 4;
	plainsBiome->m_seed = 7777;
	plainsBiome->m_hasTrees = true;
	plainsBiome->m_treesXPerlinSeed = 46738231;
	plainsBiome->m_treesYPerlinSeed = 81766411;
	plainsBiome->m_treeGridCellSide = 30;
	plainsBiome->initBiome();
	m_result = plainsBiome;
}

void BiomeBuilder::loadSavanaBiome() {
	SavanaBiome* savanaBiome = new SavanaBiome();
	savanaBiome->m_biomeId = Biome::BiomeId::SAVANA;
	savanaBiome->m_name = "Savana";
	savanaBiome->m_minTemp = 0.5f;
	savanaBiome->m_maxTemp = 0.7f;
	savanaBiome->m_minHum = 0.0f;
	savanaBiome->m_maxHum = 0.3f;
	savanaBiome->m_period = 128;
	savanaBiome->m_amplitude = 8.0f;
	savanaBiome->m_frequency = 1.0f;
	savanaBiome->m_baseHeight = m_seaLevel + 5;
	savanaBiome->m_smoothGridSize = 8;
	savanaBiome->m_terrainDetailLevels = 4;
	savanaBiome->m_seed = 3333;
	savanaBiome->m_hasTrees = true;
	savanaBiome->m_treesXPerlinSeed = 26738291;
	savanaBiome->m_treesYPerlinSeed = 81762401;
	savanaBiome->m_treeGridCellSide = 70;
	savanaBiome->initBiome();
	m_result = savanaBiome;
}

void BiomeBuilder::loadTaigaBiome() {
	TaigaBiome* taigaBiome = new TaigaBiome();
	taigaBiome->m_biomeId = Biome::BiomeId::TAIGA;
	taigaBiome->m_name = "Taiga";
	taigaBiome->m_minTemp = 0.3f;
	taigaBiome->m_maxTemp = 0.5f;
	taigaBiome->m_minHum = 0.0f;
	taigaBiome->m_maxHum = 0.3f;
	taigaBiome->m_period = 128;
	taigaBiome->m_amplitude = 8.0f;
	taigaBiome->m_frequency = 1.0f;
	taigaBiome->m_baseHeight = m_seaLevel + 5;
	taigaBiome->m_smoothGridSize = 8;
	taigaBiome->m_terrainDetailLevels = 4;
	taigaBiome->m_seed = 2222;
	taigaBiome->m_hasTrees = true;
	taigaBiome->m_treesXPerlinSeed = 46738281;
	taigaBiome->m_treesYPerlinSeed = 85762411;
	taigaBiome->m_treeGridCellSide = 6;
	taigaBiome->initBiome();
	m_result = taigaBiome;
}

void BiomeBuilder::loadTundraBiome() {
	TundraBiome* tundraBiome = new TundraBiome();
	tundraBiome->m_biomeId = Biome::BiomeId::TUNDRA;
	tundraBiome->m_name = "Tundra";
	tundraBiome->m_minTemp = 0.0f;
	tundraBiome->m_maxTemp = 0.3f;
	tundraBiome->m_minHum = 0.0f;
	tundraBiome->m_maxHum = 0.3f;
	tundraBiome->m_period = 256;
	tundraBiome->m_amplitude = 8.0f;
	tundraBiome->m_frequency = 1.0f;
	tundraBiome->m_baseHeight = m_seaLevel + 3;
	tundraBiome->m_smoothGridSize = 8;
	tundraBiome->m_terrainDetailLevels = 4;
	tundraBiome->m_seed = 1111;
	tundraBiome->m_hasTrees = true;
	tundraBiome->m_treesXPerlinSeed = 46738291;
	tundraBiome->m_treesYPerlinSeed = 81762411;
	tundraBiome->m_treeGridCellSide = 100;
	tundraBiome->initBiome();
	m_result = tundraBiome;
}

void BiomeBuilder::setSeaLevel(const unsigned int& seaLevel) {
	m_seaLevel = seaLevel;
}

void BiomeBuilder::reset() {
	m_result = nullptr;
}