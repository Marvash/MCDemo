#pragma once

#include <string>
#include <glm/glm.hpp>

class Chunk;
class Biome;

class Cube {
public:

	enum class FaceSide {
		RIGHT, 
		LEFT, 
		TOP, 
		BOTTOM, 
		FRONT, 
		BACK
	};

	enum class CubeId {
		UNGENERATED_BLOCK,
		AIR_BLOCK,
		DIRT_BLOCK,
		GRASS_BLOCK,
		STONE_BLOCK,
		SAND_BLOCK,
		SNOWY_GRASS_BLOCK,
		OAK_LOG_BLOCK,
		LEAVES_BLOCK
	};

	

	Cube();
	~Cube();
	Cube(CubeId cubeId);
	Cube(CubeId cubeId, Chunk* chunkRef, Biome* biomeRef, float xOffset, float yOffset, float zOffset);
	
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
	Chunk* getChunkRef();
	void setChunkRef(Chunk* chunk);
	Biome* getBiomeRef();
	void setBiomeRef(Biome* biome);
	bool isTransparent();
	glm::vec3 getCubeCoordsOffset();
	void getCubeIndexesOffset(int& height, int& width, int& depth);

private:
	CubeId m_cubeId;
	Chunk* m_chunkRef;
	Biome* m_biomeRef;

	glm::vec3 m_offset;
};

