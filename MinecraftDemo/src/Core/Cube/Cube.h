#pragma once

#include <string>

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
		OAK_LOG,
		LEAVES
	};

	

	Cube();
	~Cube();
	Cube(CubeId cubeId, Chunk* chunkRef, Biome* biomeRef);
	
	static std::string getDisplayName(CubeId cubeId);
	static int getNumericId(CubeId cubeId);

	CubeId getCubeId();
	void setCubeId(CubeId cubeId);
	Chunk* getChunkRef();
	void setChunkRef(Chunk* chunk);
	Biome* getBiomeRef();
	void setBiomeRef(Biome* biome);
	bool isTransparent();

private:
	CubeId cubeId;
	Chunk* chunkRef;
	Biome* biomeRef;
};

