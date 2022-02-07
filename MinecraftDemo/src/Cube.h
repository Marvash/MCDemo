#pragma once

#include "coreInclude.h"
#include "AtlasManager.h"
#include "Shader.h"
#include "Biome.h"

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
		STONE_BLOCK,
		SAND_BLOCK,
		SNOWY_GRASS_BLOCK
	};

	CubeId cubeId;
	Chunk* chunkRef;
	Biome::BiomeID biomeId;

	Cube();
	~Cube();
	Cube(CubeId cubeId, Chunk* chunkRef, Biome::BiomeID biomeId);
	
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);
	static int getAtlasTexIndex(CubeId cubeId, FaceSide faceSide);
	static int getBiomeCubeColors(Biome::BiomeID biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
	
};

