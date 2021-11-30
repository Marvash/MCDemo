#pragma once

#include "coreInclude.h"
#include "Shader.h"
#include "Cube.h"

class Chunk {
public:
	enum class ChunkState {
		// Chunk should regenerate block matrix
		SHOULDREGENERATE,
		// A thread is currently regenerating the block matrix
		ISREGENERATING,
		// Block matrix is up to date, should rebuild mesh
		SHOULDREBUILD,
		// Mesh is built
		MESHBUILT,
		// Mesh is loaded, canDraw = true
		MESHLOADED
	};

	Chunk* leftNeighbour;
	Chunk* rightNeighbour;
	Chunk* frontNeighbour;
	Chunk* backNeighbour;
	glm::vec3 chunkPosition;
	bool init;
	bool canDraw;
	ChunkState state;

	Chunk(int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	Chunk(Cube*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	~Chunk();
	void drawChunk();
	void buildMesh();
	void loadMesh();
	Cube::CubeId getBlockValue(int x, int y, int z);
	static void deleteChunkData(Cube*** chunkData, int height, int width);
	void setBlockMatrix(Cube*** chunkData);
	void setPosition(glm::vec3& position);
private:

	static const float blockSideSize;

	unsigned int VAO, VBO, EBO;
	Cube*** blockMatrix;
	int meshIndexCount;
	int newMeshIndexCount;
	int meshVertexCount;
	float* verticesCompact;
	int* indicesCompact;
	float* vertices;
	int* indices;
	int chunkHeight;
	int chunkSideSize;

	Cube::CubeId findNeighbourBlock(Cube::FaceSide neighbourSide, int height, int width, int depth);
	void renderingSetup();
	void cleanVerticesArrays();
};