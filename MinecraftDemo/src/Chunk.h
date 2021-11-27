#pragma once
#include "coreInclude.h"
#include "Shader.h"
#include "Cube.h"

class Chunk {
public:
	Chunk* leftNeighbour;
	Chunk* rightNeighbour;
	Chunk* frontNeighbour;
	Chunk* backNeighbour;
	glm::vec3 chunkPosition;
	bool init;
	bool shouldRegenerate;
	bool isMatrixUpdated;
	bool isMeshBuilt;
	bool isMeshLoaded;
	bool shouldRebuild;

	Chunk(int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	Chunk(Cube**** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	~Chunk();
	void drawChunk();
	void buildMesh();
	void loadMesh();
	Cube::CubeId getBlockValue(int x, int y, int z);
	static void deleteChunkData(Cube**** chunkData, int height, int width, int depth);
	void setBlockMatrix(Cube**** chunkData);
	void setPosition(glm::vec3& position);
private:
	enum class NeighbourSide {
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};

	static const float blockSideSize;

	unsigned int VAO, VBO, EBO;
	Cube**** blockMatrix;
	int meshIndexCount;
	int meshVertexCount;
	float* verticesCompact;
	int* indicesCompact;
	float* vertices;
	int* indices;
	int chunkHeight;
	int chunkSideSize;

	Cube::CubeId findNeighbourBlock(NeighbourSide neighbour, int height, int width, int depth);
	void renderingSetup();
	void cleanVerticesArrays();
};