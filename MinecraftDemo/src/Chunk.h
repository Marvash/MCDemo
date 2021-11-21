#pragma once
#include "coreInclude.h"
#include "Shader.h"

class Chunk {
public:
	Chunk* leftNeighbour;
	Chunk* rightNeighbour;
	Chunk* frontNeighbour;
	Chunk* backNeighbour;
	glm::vec3 chunkPosition;
	bool init;

	Chunk(int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	Chunk(int*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	~Chunk();
	void drawChunk();
	void buildMesh();
	int getBlockValue(int x, int y, int z);
	static void deleteChunkData(int*** chunkData, int height, int width);
private:
	enum class NeighbourSide {
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};

	static const float blockSideSize;
	static const float textureOffset;

	unsigned int VAO, VBO, EBO;
	int*** blockMatrix;
	int meshVertexCount;
	float* verticesCompact;
	int* indicesCompact;
	float* vertices;
	int* indices;
	int chunkHeight;
	int chunkSideSize;

	int findNeighbourBlock(NeighbourSide neighbour, int height, int width, int depth);
	void renderingSetup();
};