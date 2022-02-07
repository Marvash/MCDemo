#include "Cube.h"

Cube::Cube() : cubeId(CubeId::AIR_BLOCK), chunkRef(nullptr), biomeId(Biome::BiomeID::FOREST ) {

}

Cube::Cube(CubeId cubeId, Chunk* chunkRef, Biome::BiomeID biomeId) : cubeId(cubeId), chunkRef(chunkRef), biomeId(biomeId) {

}

Cube::~Cube() {
}

std::string Cube::getDisplayName(CubeId cubeId) {

}

int Cube::getNumericId(CubeId cubeId) {

}

int Cube::getAtlasTexIndex(CubeId cubeId, FaceSide faceSide) {
	switch (cubeId) {
	case CubeId::GRASS_BLOCK:
		switch (faceSide) {
		case FaceSide::RIGHT:
		case FaceSide::LEFT:
		case FaceSide::FRONT:
		case FaceSide::BACK:
			return 0;
		case FaceSide::TOP:
			return 24;
		case FaceSide::BOTTOM:
			return 48;
		}
		break;
	case CubeId::DIRT_BLOCK:
		return 72;
	case CubeId::STONE_BLOCK:
		return 96;
	case CubeId::SAND_BLOCK:
		return 120;
	case CubeId::SNOWY_GRASS_BLOCK:
		switch (faceSide) {
		case FaceSide::RIGHT:
		case FaceSide::LEFT:
		case FaceSide::FRONT:
		case FaceSide::BACK:
			return 144;
		case FaceSide::TOP:
			return 168;
		case FaceSide::BOTTOM:
			return 192;
		}
		break;
	}
	return -1;
}

int Cube::getBiomeCubeColors(Biome::BiomeID biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	switch (biomeId) {
	case Biome::BiomeID::TUNDRA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 198;
			case FaceSide::TOP:
				return 207;
			case FaceSide::BOTTOM:
				return 216;
			}
			break;
		}
		break;
	case Biome::BiomeID::TAIGA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 225;
			case FaceSide::TOP:
				return 234;
			case FaceSide::BOTTOM:
				return 243;
			}
			break;
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 36;
			case FaceSide::TOP:
				return 45;
			case FaceSide::BOTTOM:
				return 54;
			}
			break;
		}
		break;
	case Biome::BiomeID::SAVANA:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 90;
			case FaceSide::TOP:
				return 99;
			case FaceSide::BOTTOM:
				return 108;
			}
			break;
		}
		break;
	case Biome::BiomeID::DESERT:
		break;
	case Biome::BiomeID::MOUNTAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 117;
			case FaceSide::TOP:
				return 126;
			case FaceSide::BOTTOM:
				return 135;
			}
			break;
		}
		break;
	case Biome::BiomeID::HILLS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 144;
			case FaceSide::TOP:
				return 153;
			case FaceSide::BOTTOM:
				return 162;
			}
			break;
		}
		break;
	case Biome::BiomeID::PLAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 9;
			case FaceSide::TOP:
				return 18;
			case FaceSide::BOTTOM:
				return 27;
			}
			break;
		}
		break;
	case Biome::BiomeID::FOREST:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 63;
			case FaceSide::TOP:
				return 72;
			case FaceSide::BOTTOM:
				return 81;
			}
			break;
		}
		break;
	case Biome::BiomeID::JUNGLE:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case FaceSide::RIGHT:
			case FaceSide::LEFT:
			case FaceSide::FRONT:
			case FaceSide::BACK:
				return 171;
			case FaceSide::TOP:
				return 180;
			case FaceSide::BOTTOM:
				return 189;
			}
			break;
		}
		break;
	}
	return 0;
}

Cube::CubeId Cube::getCubeId() {
	return cubeId;
}

void Cube::setCubeId(Cube::CubeId cubeId) {
	this->cubeId = cubeId;
}