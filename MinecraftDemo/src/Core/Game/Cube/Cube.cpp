#include "Cube.h"

Cube::Cube() : cubeId(CubeId::AIR_BLOCK), chunkRef(nullptr), biomeRef(nullptr) {

}

Cube::Cube(CubeId cubeId, Chunk* chunkRef, Biome* biomeRef) : cubeId(cubeId), chunkRef(chunkRef), biomeRef(nullptr) {
}

Cube::~Cube() {
}

bool Cube::isTransparent() {
	return this->cubeId == CubeId::AIR_BLOCK || this->cubeId == CubeId::LEAVES;
}

std::string Cube::getDisplayName(CubeId cubeId) {
	return std::string("");
}

int Cube::getNumericId(CubeId cubeId) {
	return 0;
}

Cube::CubeId Cube::getCubeId() {
	return cubeId;
}

void Cube::setCubeId(CubeId cubeId) {
	this->cubeId = cubeId;
}

Chunk* Cube::getChunkRef() {
	return chunkRef;
}

void Cube::setChunkRef(Chunk* chunk) {
	chunkRef = chunk;
}

Biome* Cube::getBiomeRef() {
	return biomeRef;
}

void Cube::setBiomeRef(Biome* biome) {
	biomeRef = biome;
}