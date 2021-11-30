#pragma once

#include "coreInclude.h"
#include "Chunk.h"
#include "Cube.h"
#include "PerlinNoiseGenerator.h"

class ChunkManager {
public:
	static const int chunkSideSize;
	static const int chunkHeight;
	static const int seaLevelOffset;

	ChunkManager(glm::vec3 origin);
	~ChunkManager();
	void generateChunks();
	void drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view);
	void updatePlayerPosition(glm::vec3& playerPos);
	void rebuildChunks();
	void reloadChunks();
	void startBuilderThreads();
	void startGeneratorThreads();
	void startOriginUpdaterThreads();

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
	PerlinNoiseGenerator perlinGen;
	boost::mutex internalLock;
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