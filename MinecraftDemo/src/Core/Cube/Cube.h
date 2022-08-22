#pragma once
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include "CubeIdEnum.h"
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

	Cube();
	~Cube();
	Cube(CubeId cubeId);
	Cube(CubeId cubeId, Chunk* chunkRef, Biome* biomeRef, float xOffset, float yOffset, float zOffset);
	
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);
	static bool isTransparent(CubeId cubeId);
	static bool canBeRendered(CubeId cubeId);
	static ItemId getItemId(CubeId cubeId);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
	Chunk* getChunkRef();
	void setChunkRef(Chunk* chunk);
	Biome* getBiomeRef();
	void setBiomeRef(Biome* biome);
	glm::vec3 getCubeCoordsOffset();
	void getCubeIndexesOffset(int& height, int& width, int& depth);

private:
	CubeId m_cubeId;
	Chunk* m_chunkRef;
	Biome* m_biomeRef;

	glm::vec3 m_offset;
};

