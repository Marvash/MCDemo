#pragma once

#include "coreInclude.h"
#include "AtlasManager.h"

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

	Cube();
	Cube(CubeId cubeId);
	static void init();
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);
	static float* getAtlasTexCoords(CubeId cubeId, FaceSide faceSide);
	static float* getTexColor(CubeId cubeId, FaceSide faceSide);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
private:
	static float* grassBlockTexCoords;
	static float* grassBlockTexColors;
};

