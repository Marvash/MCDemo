#pragma once

#include "coreInclude.h"
#include "Shader.h"
#include "Cube.h"
#include "ChunkManager.h"

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
	Cube* getBlockValue(int x, int y, int z);
	static void deleteChunkData(Cube*** chunkData, int height, int width);
	void setBlockMatrix(Cube*** chunkData);
	void setPosition(glm::vec3& position);
	Cube* getCubeByCoords(glm::vec3 coords);
	Cube* findNeighbourBlock(Cube::FaceSide neighbourSide, int height, int width, int depth);
	Cube* findNeighbourBlock(Cube::FaceSide neighbourSide, Cube* cube);
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

	void renderingSetup();
	void cleanVerticesArrays();
};