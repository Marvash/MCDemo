#include "Chunk.h"

const float Chunk::blockSideSize = 1.0f;

Chunk::Chunk(int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight),
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	init(false),
	state(ChunkState::SHOULDREGENERATE),
	canDraw(false) {
	blockMatrix = nullptr;
}

Chunk::Chunk(Cube*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight), 
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	vertices(nullptr),
	verticesCompact(nullptr),
	indices(nullptr),
	indicesCompact(nullptr),
	init(false),
	state(ChunkState::SHOULDREGENERATE),
	canDraw(false) {
	this->blockMatrix = blockMatrix;
}

void Chunk::setBlockMatrix(Cube*** chunkData) {
	if (blockMatrix != nullptr) {
		deleteChunkData(blockMatrix, chunkHeight, chunkSideSize);
	}
	blockMatrix = chunkData;
}

void Chunk::setPosition(glm::vec3& position) {
	chunkPosition = position;
}

void Chunk::renderingSetup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 13 * sizeof(float), (void*)(10 * sizeof(float)));
	glBindVertexArray(0);
	init = true;
}

void Chunk::drawChunk() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, meshIndexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Chunk::loadMesh() {
	if (!init)
		renderingSetup();
	size_t vertexDataSize = (size_t)meshVertexCount * (size_t)13;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexDataSize, verticesCompact, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	meshIndexCount = newMeshIndexCount;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (meshIndexCount), indicesCompact, GL_STATIC_DRAW);
	glBindVertexArray(0);
	cleanVerticesArrays();
}

void Chunk::buildMesh() {
	cleanVerticesArrays();
	size_t verticesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)(13 * 4 * 6);
	size_t indicesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)36;
	vertices = new float[verticesMaxSize];
	indices = new int[indicesMaxSize];
	int correctVertexCount = 0;
	int correctIndexCount = 0;
	int vertexIndexBase = 0;
	for (int i = 0; i < chunkHeight; i++) {
		for (int j = 0; j < chunkSideSize; j++) {
			for (int w = 0; w < chunkSideSize; w++) {
				if (blockMatrix[i][j][w].cubeId == Cube::CubeId::AIR_BLOCK) {
					continue;
				}
				float vertexBaseHeight = i + (blockSideSize / 2.0f);
				float vertexBaseWidth = j - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				float vertexBaseDepth = w - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				int vertexBaseIndex = correctVertexCount * 13;
				float* texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::TOP);
				float* colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::TOP);
				// TOP
				Cube* neighbourCube = findNeighbourBlock(Cube::FaceSide::TOP, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 3;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexBaseIndex = correctVertexCount * 13;
				texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::BOTTOM);
				colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::BOTTOM);
				// BOTTOM
				neighbourCube = findNeighbourBlock(Cube::FaceSide::BOTTOM, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexBaseIndex = correctVertexCount * 13;
				texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::RIGHT);
				colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::RIGHT);
				// RIGHT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::RIGHT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 2;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexBaseIndex = correctVertexCount * 13;
				texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::LEFT);
				colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::LEFT);
				// LEFT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::LEFT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 1;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexBaseIndex = correctVertexCount * 13;
				texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::FRONT);
				colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::FRONT);
				// FRONT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::FRONT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 1;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexBaseIndex = correctVertexCount * 13;
				texCoords = Cube::getAtlasTexCoords(blockMatrix[i][j][w].cubeId, Cube::FaceSide::BACK);
				colors = Cube::getTexColor(blockMatrix[i][j][w].cubeId, Cube::FaceSide::BACK);
				// BACK
				neighbourCube = findNeighbourBlock(Cube::FaceSide::BACK, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->cubeId == Cube::CubeId::AIR_BLOCK) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[4];
					vertices[vertexBaseIndex++] = texCoords[5];
					vertices[vertexBaseIndex++] = texCoords[6];
					vertices[vertexBaseIndex++] = texCoords[7];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[12];
					vertices[vertexBaseIndex++] = texCoords[13];
					vertices[vertexBaseIndex++] = texCoords[14];
					vertices[vertexBaseIndex++] = texCoords[15];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[8];
					vertices[vertexBaseIndex++] = texCoords[9];
					vertices[vertexBaseIndex++] = texCoords[10];
					vertices[vertexBaseIndex++] = texCoords[11];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = texCoords[0];
					vertices[vertexBaseIndex++] = texCoords[1];
					vertices[vertexBaseIndex++] = texCoords[2];
					vertices[vertexBaseIndex++] = texCoords[3];
					vertices[vertexBaseIndex++] = colors[0];
					vertices[vertexBaseIndex++] = colors[1];
					vertices[vertexBaseIndex++] = colors[2];
					vertices[vertexBaseIndex++] = colors[3];
					vertices[vertexBaseIndex++] = colors[4];
					vertices[vertexBaseIndex++] = colors[5];

					int base = vertexIndexBase;

					indices[correctIndexCount++] = base;
					indices[correctIndexCount++] = base + 2;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 1;
					indices[correctIndexCount++] = base + 3;
					indices[correctIndexCount++] = base + 2;

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
			}
		}
	}

	if (correctIndexCount > 0 && correctVertexCount > 2) {
		newMeshIndexCount = correctIndexCount;
		meshVertexCount = correctVertexCount;
		size_t vertexDataSize = (size_t)meshVertexCount * (size_t)13;
		verticesCompact = new float[vertexDataSize];
		indicesCompact = new int[newMeshIndexCount];
		for (int i = 0; i < vertexDataSize; i++) {
			verticesCompact[i] = vertices[i];
		}
		
		for (int i = 0; i < newMeshIndexCount; i++) {
			indicesCompact[i] = indices[i];
		}
	}
}

void Chunk::cleanVerticesArrays() {
	delete[] verticesCompact;
	delete[] indicesCompact;
	verticesCompact = nullptr;
	indicesCompact = nullptr;
	delete[] vertices;
	delete[] indices;
	vertices = nullptr;
	indices = nullptr;
}

Cube* Chunk::getCubeByCoords(glm::vec3& coords) {
	glm::vec3 originChunkPos = chunkPosition;
	originChunkPos.x = originChunkPos.x - (chunkSideSize / 2.0f);
	originChunkPos.z = originChunkPos.z - (chunkSideSize / 2.0f);
	if (glm::abs(coords.x - originChunkPos.x) > chunkSideSize || glm::abs(coords.z - originChunkPos.z) > chunkSideSize || coords.y < originChunkPos.y || coords.y >= (chunkHeight + originChunkPos.y) || state < ChunkState::SHOULDREBUILD) {
		return nullptr;
	}
	int cubeWidthIndex = glm::abs(glm::floor((coords.x - originChunkPos.x)));
	int cubeDepthIndex = glm::abs(glm::floor((coords.z - originChunkPos.z)));
	int cubeHeightIndex = glm::abs(glm::floor((coords.y - originChunkPos.y)));
	return &blockMatrix[cubeHeightIndex][cubeWidthIndex][cubeDepthIndex];
}

Cube* Chunk::getBlockValue(int height, int width, int depth) {
	return &blockMatrix[height][width][depth];
}

Cube* Chunk::findNeighbourBlock(Cube::FaceSide neighbourSide, int height, int width, int depth) {
	Chunk* neighbourChunk = nullptr;
	Cube* neighbourCube = nullptr;
	switch (neighbourSide) {
	case Cube::FaceSide::LEFT:
		if (width == 0) {
			neighbourChunk = leftNeighbour;
			width = chunkSideSize - 1;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width -= 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::RIGHT:
		if (width == (chunkSideSize - 1)) {
			neighbourChunk = rightNeighbour;
			width = 0;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width += 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::FRONT:
		if (depth == (chunkSideSize - 1)) {
			neighbourChunk = frontNeighbour;
			depth = 0;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth += 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::BACK:
		if (depth == 0) {
			neighbourChunk = backNeighbour;
			depth = chunkSideSize - 1;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth -= 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::TOP:
		if (height != (chunkHeight - 1)) {
			height += 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::BOTTOM:
		if (height != 0) {
			height -= 1;
			neighbourCube = &blockMatrix[height][width][depth];
		}
		break;
	}
	return neighbourCube;
}

Cube* Chunk::findNeighbourBlock(Cube::FaceSide neighbourSide, Cube* cube) {
	int height, width, depth;
	for (height = 0; height < chunkHeight; height++) {
		for (width = 0; width < chunkSideSize; width++) {
			for (depth = 0; depth < chunkSideSize; depth++) {
				if (&blockMatrix[height][width][depth] == cube) {
					return findNeighbourBlock(neighbourSide, height, width, depth);
				}
			}
		}
	}
	return nullptr;
}

Chunk::~Chunk() {
	if (leftNeighbour != nullptr) {
		leftNeighbour->rightNeighbour = nullptr;
	}
	if (rightNeighbour != nullptr) {
		rightNeighbour->leftNeighbour = nullptr;
	}
	if (backNeighbour != nullptr) {
		backNeighbour->frontNeighbour = nullptr;
	}
	if (frontNeighbour != nullptr) {
		frontNeighbour->backNeighbour = nullptr;
	}
	glDeleteVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glDeleteBuffers(1, &VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glDeleteBuffers(1, &EBO);
	deleteChunkData(blockMatrix, chunkHeight, chunkSideSize);
	cleanVerticesArrays();
}

void Chunk::deleteChunkData(Cube*** chunkData, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete[] chunkData[i][j];
		}
		delete[] chunkData[i];
	}
	delete[] chunkData;
}