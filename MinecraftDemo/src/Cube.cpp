#include "Cube.h"

Cube::Cube() : cubeId(CubeId::AIR_BLOCK), chunkRef(nullptr) {

}

Cube::Cube(CubeId cubeId, Chunk* chunkRef) : cubeId(cubeId), chunkRef(chunkRef) {

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
		return 99;
		break;
	case CubeId::STONE_BLOCK:
		return 132;
		break;
	}
	return -1;
}
int Cube::getTexColor(CubeId cubeId, FaceSide faceSide) {
	switch (cubeId) {
	case CubeId::GRASS_BLOCK:
		switch (faceSide) {
		case FaceSide::RIGHT:
		case FaceSide::LEFT:
		case FaceSide::FRONT:
		case FaceSide::BACK:
			return 72;
			break;
		case FaceSide::TOP:
			return 81;
			break;
		case FaceSide::BOTTOM:
			return 90;
			break;
		}
		break;
	case CubeId::DIRT_BLOCK:
		return 123;
		break;
	case CubeId::STONE_BLOCK:
		return 156;
		break;
	}
	return -1;
}

Cube::CubeId Cube::getCubeId() {
	return cubeId;
}

void Cube::setCubeId(Cube::CubeId cubeId) {
	this->cubeId = cubeId;
}