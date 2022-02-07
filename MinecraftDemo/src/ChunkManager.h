#pragma once

#include "coreInclude.h"
#include "Chunk.h"
#include "Cube.h"
#include "RayCast.h"
#include "TerrainGenerator.h"


class ChunkManager {
public:
	static const int chunkSideSize;
	static const int chunkHeight;
	static const int seaLevelOffset;
	boost::mutex internalLockLP;
	boost::mutex internalLockNext;
	boost::mutex internalLockData;
	int test = 0;
	TerrainGenerator terrainGen;

	ChunkManager(glm::vec3 origin);
	~ChunkManager();
	void generateChunks();
	void drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view);
	void rebuildChunks();
	void reloadChunks();
	void startBuilderThreads();
	void startGeneratorThreads();
	void destroyBlock();
	void placeBlock(Cube::CubeId cubeId);
	void updateGenerationOrigin(glm::vec3& playerPos, glm::vec3& playerLookDir);
	Cube* getCubeByCoords(glm::vec3 coords);

private:
	enum class ChunkSide {
		LEFT,
		RIGHT,
		BOTTOM,
		TOP
	};

	static const int chunkArrayWidth;
	static const int chunkArrayDepth;
	static const int nWorkersRegen;
	static const int nWorkersRebuild;

	Chunk*** chunkMatrix;
	glm::vec3 generationOrigin;
	glm::vec3 playerPosition;
	glm::vec3 playerLookDirection;
	
	
	bool buildersShouldStop;
	bool generatorsShouldStop;
	boost::thread_group generatorThreads;
	boost::thread_group builderThreads;

	void generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex, Chunk* original);
	void resetNeighbours();
	void moveChunkMatrix(ChunkSide side);
	void generatorThreadFunction();
	void builderThreadFunction();

	void lockHP();
	void unlockHP();
	void lockLP();
	void unlockLP();
};