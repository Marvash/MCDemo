#include "BiomeLibrary.h"

BiomeLibrary::BiomeLibrary(CoreEventDispatcher* coreEventDispatcher) : CoreService(coreEventDispatcher) {
}

void BiomeLibrary::init() {
	initBiomesArray();
	m_biomeColorsBuffer = new TextureBuffer(m_biomeColors.m_biomeColorsArray, m_biomeColors.TEX_COLORS_SIZE);
}

void BiomeLibrary::initBiomesArray() {
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

Biome** BiomeLibrary::getBiomes() {
	return m_biomes;
}

unsigned int BiomeLibrary::getBiomesCount() {
	return m_biomesCount;
}

TextureBuffer* BiomeLibrary::getBiomeColorsBuffer() {
	return m_biomeColorsBuffer;
}

void BiomeLibrary::onNotify(Event& newEvent) {

}

void BiomeLibrary::notify(Event& newEvent) {

}

int BiomeLibrary::getBiomeCubeColors(Biome::BiomeId biomeId, BlockId blockId, BlockFace faceSide) {
	switch (biomeId) {
	case Biome::BiomeId::TUNDRA:
		switch (blockId) {
		case BlockId::SNOWY_GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 198;
			case BlockFace::TOP:
				return 207;
			case BlockFace::BOTTOM:
				return 216;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::TAIGA:
		switch (blockId) {
		case BlockId::SNOWY_GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 225;
			case BlockFace::TOP:
				return 234;
			case BlockFace::BOTTOM:
				return 243;
			}
			break;
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 36;
			case BlockFace::TOP:
				return 45;
			case BlockFace::BOTTOM:
				return 54;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::SAVANA:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 90;
			case BlockFace::TOP:
				return 99;
			case BlockFace::BOTTOM:
				return 108;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::DESERT:
		break;
	case Biome::BiomeId::MOUNTAINS:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 117;
			case BlockFace::TOP:
				return 126;
			case BlockFace::BOTTOM:
				return 135;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::HILLS:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 144;
			case BlockFace::TOP:
				return 153;
			case BlockFace::BOTTOM:
				return 162;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::PLAINS:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 9;
			case BlockFace::TOP:
				return 18;
			case BlockFace::BOTTOM:
				return 27;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::FOREST:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 63;
			case BlockFace::TOP:
				return 72;
			case BlockFace::BOTTOM:
				return 81;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::JUNGLE:
		switch (blockId) {
		case BlockId::GRASS:
			switch (faceSide) {
			case BlockFace::RIGHT:
			case BlockFace::LEFT:
			case BlockFace::FRONT:
			case BlockFace::BACK:
				return 171;
			case BlockFace::TOP:
				return 180;
			case BlockFace::BOTTOM:
				return 189;
			}
			break;
		case BlockId::LEAVES:
			return 252;
		}
		break;
	}
	return 0;
}