#include "Cube.h"

Cube::Cube() : 
	m_cubeId(CubeId::UNGENERATED_BLOCK), 
	m_chunkRef(nullptr), 
	m_biomeRef(nullptr),
	m_offset(glm::vec3(0.0f, 0.0f, 0.0f)) {

}

Cube::Cube(CubeId cubeId, Chunk* chunkRef, Biome* biomeRef, float xOffset, float yOffset, float zOffset) :
	m_cubeId(cubeId), 
	m_chunkRef(chunkRef), 
	m_biomeRef(nullptr),
	m_offset(glm::vec3(xOffset, yOffset, zOffset)) {
}

Cube::~Cube() {
}

bool Cube::isTransparent(CubeId cubeId) {
	return cubeId == CubeId::AIR_BLOCK || cubeId == CubeId::LEAVES_BLOCK || cubeId == CubeId::UNGENERATED_BLOCK;
}

bool Cube::canBeRendered(CubeId cubeId) {
	return !(cubeId == CubeId::AIR_BLOCK || cubeId == CubeId::UNGENERATED_BLOCK);
}

glm::vec3 Cube::getCubeCoordsOffset() {
	return m_offset;
}

void Cube::getCubeIndexesOffset(int& height, int& width, int& depth) {
	height = int(m_offset.y);
	width = int(m_offset.x);
	depth = int(m_offset.z);
}

ItemId Cube::getItemId(CubeId cubeId) {
	switch (cubeId) {
	case CubeId::DIRT_BLOCK:
		return ItemId::DIRT_BLOCK_ITEM;
	case CubeId::GRASS_BLOCK:
		return ItemId::GRASS_BLOCK_ITEM;
	case CubeId::LEAVES_BLOCK:
		return ItemId::LEAVES_BLOCK_ITEM;
	case CubeId::OAK_LOG_BLOCK:
		return ItemId::OAK_LOG_BLOCK_ITEM;
	case CubeId::SAND_BLOCK:
		return ItemId::SAND_BLOCK_ITEM;
	case CubeId::SNOWY_GRASS_BLOCK:
		return ItemId::SNOWY_GRASS_BLOCK_ITEM;
	case CubeId::STONE_BLOCK:
		return ItemId::STONE_BLOCK_ITEM;
	}
	return ItemId::NONE;
}

std::string Cube::getDisplayName(CubeId cubeId) {
	switch (cubeId) {
	case CubeId::AIR_BLOCK:
		return std::string("Air Block");
	case CubeId::DIRT_BLOCK:
		return std::string("Dirt Block");
	case CubeId::GRASS_BLOCK:
		return std::string("Grass Block");
	case CubeId::LEAVES_BLOCK:
		return std::string("Leaves Block");
	case CubeId::OAK_LOG_BLOCK:
		return std::string("Oak Log Block");
	case CubeId::SAND_BLOCK:
		return std::string("Sand Block");
	case CubeId::SNOWY_GRASS_BLOCK:
		return std::string("Snowy Grass Block");
	case CubeId::STONE_BLOCK:
		return std::string("Stone Block");
	case CubeId::UNGENERATED_BLOCK:
		return std::string("Ungenerated Block");
	}
	return std::string("Unknown Block");
}

int Cube::getNumericId(CubeId cubeId) {
	return 0;
}

CubeId Cube::getCubeId() {
	return m_cubeId;
}

void Cube::setCubeId(CubeId cubeId) {
	this->m_cubeId = cubeId;
}

Chunk* Cube::getChunkRef() {
	return m_chunkRef;
}

void Cube::setChunkRef(Chunk* chunk) {
	m_chunkRef = chunk;
}

Biome* Cube::getBiomeRef() {
	return m_biomeRef;
}

void Cube::setBiomeRef(Biome* biome) {
	m_biomeRef = biome;
}