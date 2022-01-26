#pragma once

#include "coreInclude.h"
#include "AtlasManager.h"
#include "Shader.h"

class Chunk;

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
		AIR_BLOCK,
		DIRT_BLOCK,
		GRASS_BLOCK,
		STONE_BLOCK
	};

	CubeId cubeId;
	Chunk* chunkRef;

	Cube();
	~Cube();
	Cube(CubeId cubeId, Chunk* chunkRef);
	
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);
	static int getAtlasTexIndex(CubeId cubeId, FaceSide faceSide);
	static int getTexColor(CubeId cubeId, FaceSide faceSide);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
	
};

