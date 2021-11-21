#pragma once

#include "coreInclude.h"
#include "Chunk.h"
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
	void updateGenerationOrigin(glm::vec3& playerPos);
	void rebuildChunks();
	void startBuilderThread();
private:
	enum class ChunkSide {
		LEFT,
		RIGHT,
		BOTTOM,
		TOP
	};

	static const int chunkArrayWidth;
	static const int chunkArrayDepth;

	Chunk*** chunkMatrix;
	glm::vec3 generationOrigin;
	PerlinNoiseGenerator perlinGen;
	boost::mutex internalLock;
	bool** rebuildMatrix;
	boost::thread builderThread;
	bool builderShouldStop;

	void generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex);
	void resetNeighbours();
	void moveChunkMatrix(ChunkSide side);
	void builderThreadFunction();
};