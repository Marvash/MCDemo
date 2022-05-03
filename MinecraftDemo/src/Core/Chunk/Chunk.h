#pragma once
#include "Core/Cube/Cube.h"
#include <Boost/log/trivial.hpp>
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/BiomeManager/BiomeManager.h"

struct ChunkRenderData {
	GLuint VAO;
	unsigned int indexCount;
	glm::vec3 position;
};

class CoreServiceLocator;

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

	Chunk(BiomeManager* biomeManager, Atlas* atlas, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	Chunk(BiomeManager* biomeManager, Atlas* atlas, Cube*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	~Chunk();
	void buildMesh();
	void loadMesh();
	Cube* getBlockValue(int x, int y, int z);
	static void deleteChunkData(Cube*** chunkData, int height, int width);
	Cube*** getBlockMatrix();
	void setPosition(glm::vec3& position);
	Cube* getCubeByCoords(glm::vec3 coords);
	Cube* findNeighbourBlock(Cube::FaceSide neighbourSide, int height, int width, int depth);
	Cube* findNeighbourBlock(Cube::FaceSide neighbourSide, Cube* cube);
	ChunkRenderData& getChunkRenderData();
private:

	static const float blockSideSize;

	GLuint VAO, VBOVCoords, VBOVTexIndexes, EBO;
	Cube*** m_blockMatrix;
	size_t meshIndexesCount;
	size_t newMeshIndexesCount;
	size_t meshVertexesCount;
	size_t newMeshVertexesCount;
	GLfloat* vertexesCoordinatesCompact;
	GLfloat* vertexesCoordinates;
	GLuint* indexesCompact;
	GLuint* indexes;
	GLint* vertexesTexIndexesCompact;
	GLint* vertexesTexIndexes;
	ChunkRenderData renderData;
	Atlas* m_atlas;
	BiomeManager* m_biomeManager;
	int chunkHeight;
	int chunkSideSize;

	void renderingSetup();
	void addFaceCoordinates(size_t& vertexCoordsBaseIndex, Cube::FaceSide faceSide, float vertexBaseHeight, float vertexBaseWidth, float vertexBaseDepth);
	void addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex);
	void addFaceIndexes(GLuint vertexBaseIndex, size_t& indexCount);
	void cleanVerticesArrays();
	void initEmptyBlockMatrix();
};