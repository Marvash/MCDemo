#include "BiomeManager.h"

BiomeManager::BiomeManager(CoreEventDispatcher* coreEventDispatcher) : CoreService(coreEventDispatcher) {
}

void BiomeManager::init() {
	initBiomesArray();
	m_biomeColorsBuffer = new TextureBuffer(m_biomeColors.m_biomeColorsArray, m_biomeColors.TEX_COLORS_SIZE);
}

void BiomeManager::initBiomesArray() {
	if (m_biomesCount == 0) {

		m_biomesCount = 9;

		BiomeBuilder biomeBuilder(SEA_LEVEL);

		m_biomes = new Biome * [m_biomesCount];

		biomeBuilder.loadTundraBiome();
		m_biomes[0] = biomeBuilder.getResult();
		biomeBuilder.loadTaigaBiome();
		m_biomes[1] = biomeBuilder.getResult();
		biomeBuilder.loadSavanaBiome();
		m_biomes[2] = biomeBuilder.getResult();
		biomeBuilder.loadDesertBiome();
		m_biomes[3] = biomeBuilder.getResult();
		biomeBuilder.loadMountainsBiome();
		m_biomes[4] = biomeBuilder.getResult();
		biomeBuilder.loadHillsBiome();
		m_biomes[5] = biomeBuilder.getResult();
		biomeBuilder.loadPlainsBiome();
		m_biomes[6] = biomeBuilder.getResult();
		biomeBuilder.loadForestBiome();
		m_biomes[7] = biomeBuilder.getResult();
		biomeBuilder.loadJungleBiome();
		m_biomes[8] = biomeBuilder.getResult();
	}
}

Biome** BiomeManager::getBiomes() {
	return m_biomes;
}

unsigned int BiomeManager::getBiomesCount() {
	return m_biomesCount;
}

TextureBuffer* BiomeManager::getBiomeColorsBuffer() {
	return m_biomeColorsBuffer;
}

void BiomeManager::onNotify(Event& newEvent) {

}

void BiomeManager::notify(Event& newEvent) {

}

int BiomeManager::getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	switch (biomeId) {
	case Biome::BiomeId::TUNDRA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 198;
			case Cube::FaceSide::TOP:
				return 207;
			case Cube::FaceSide::BOTTOM:
				return 216;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::TAIGA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 225;
			case Cube::FaceSide::TOP:
				return 234;
			case Cube::FaceSide::BOTTOM:
				return 243;
			}
			break;
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 36;
			case Cube::FaceSide::TOP:
				return 45;
			case Cube::FaceSide::BOTTOM:
				return 54;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::SAVANA:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 90;
			case Cube::FaceSide::TOP:
				return 99;
			case Cube::FaceSide::BOTTOM:
				return 108;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::DESERT:
		break;
	case Biome::BiomeId::MOUNTAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 117;
			case Cube::FaceSide::TOP:
				return 126;
			case Cube::FaceSide::BOTTOM:
				return 135;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::HILLS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 144;
			case Cube::FaceSide::TOP:
				return 153;
			case Cube::FaceSide::BOTTOM:
				return 162;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::PLAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 9;
			case Cube::FaceSide::TOP:
				return 18;
			case Cube::FaceSide::BOTTOM:
				return 27;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::FOREST:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 63;
			case Cube::FaceSide::TOP:
				return 72;
			case Cube::FaceSide::BOTTOM:
				return 81;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	case Biome::BiomeId::JUNGLE:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 171;
			case Cube::FaceSide::TOP:
				return 180;
			case Cube::FaceSide::BOTTOM:
				return 189;
			}
			break;
		case Cube::CubeId::LEAVES_BLOCK:
			return 252;
		}
		break;
	}
	return 0;
}