#pragma once
#include "Core/Services/BlockLibrary/Block.h"
#include "Core/Services/BlockLibrary/BlockFaceEnum.h"
#include <Boost/log/trivial.hpp>
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/Biome/BiomeLibrary.h"
#include "Core/Components/RenderingComponent.h"

class BlockManager;

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
		// Mesh is loaded
		MESHLOADED
	};

	Chunk(BlockManager* blockManager, BiomeLibrary* biomeManager, Atlas* atlas, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	Chunk(BlockManager* blockManager, BiomeLibrary* biomeManager, Atlas* atlas, Block*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition);
	~Chunk();
	void buildMesh();
	void loadMesh();
	Block* getBlockValue(int x, int y, int z);
	static void deleteChunkData(Block*** chunkData, int height, int width);
	Block*** getBlockMatrix();
	void setPosition(glm::vec3& position);
	Block* getCubeByCoords(glm::f64vec3 coords);
	Block* findNeighbourBlock(BlockFace neighbourSide, int height, int width, int depth);
	Block* findNeighbourBlock(BlockFace neighbourSide, Block* cube);
	void forceChunkMeshUpdate();
	RenderingComponent* getRenderingComponent();

	Chunk* leftNeighbour;
	Chunk* rightNeighbour;
	Chunk* frontNeighbour;
	Chunk* backNeighbour;
	glm::vec3 chunkPosition;
	bool init;
	ChunkState state;
	
private:

	void renderingSetup();
	void addFaceCoordinates(size_t& vertexCoordsBaseIndex, BlockFace faceSide, float vertexBaseHeight, float vertexBaseWidth, float vertexBaseDepth);
	void addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex, int secondaryTextureCoordinatesIndex);
	void addFaceIndexes(GLuint vertexBaseIndex, size_t& indexCount);
	void cleanVerticesArrays();
	void initEmptyBlockMatrix();

	static const float blockSideSize;

	GLuint VAO, VBOVCoords, VBOVTexIndexes, EBO;
	Block*** m_blockMatrix;
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
	RenderingComponent m_renderingComponent;
	BlockManager* m_blockManager;

	Atlas* m_atlas;
	BiomeLibrary* m_biomeManager;
	int chunkHeight;
	int chunkSideSize;
};