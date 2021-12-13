#pragma once

#include "coreInclude.h"
#include "Chunk.h"
#include "Cube.h"
#include "PerlinNoiseGenerator.h"
#include "RayCast.h"

class ChunkManager {
public:
	static const int chunkSideSize;
	static const int chunkHeight;
	static const int seaLevelOffset;
	boost::mutex internalLock;

	ChunkManager(glm::vec3 origin);
	~ChunkManager();
	void generateChunks();
	void drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view);
	void updatePlayerData(glm::vec3& playerPos, glm::vec3& playerLookDir);
	void rebuildChunks();
	void reloadChunks();
	void startBuilderThreads();
	void startGeneratorThreads();
	void startOriginUpdaterThreads();
	void destroyBlock();
	void placeBlock(Cube::CubeId cubeId);
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
	static const int nWorkersUpdate;

	Chunk*** chunkMatrix;
	glm::vec3 generationOrigin;
	glm::vec3 playerPosition;
	glm::vec3 playerLookDirection;
	PerlinNoiseGenerator perlinGen;
	
	bool buildersShouldStop;
	bool generatorsShouldStop;
	bool updaterShouldStop;
	boost::thread_group generatorThreads;
	boost::thread_group builderThreads;
	boost::thread_group originUpdaterThreads;

	void generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex, Chunk* original);
	void resetNeighbours();
	void moveChunkMatrix(ChunkSide side);
	void generatorThreadFunction();
	void builderThreadFunction();
	void originUpdaterThreadFunction();
	void updateGenerationOrigin();
};