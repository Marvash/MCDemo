#include "Chunk.h"

const float Chunk::blockSideSize = 1.0f;
const float Chunk::textureOffset = 0.0001f;

Chunk::Chunk(int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr), 
	rightNeighbour(nullptr), 
	frontNeighbour(nullptr), 
	backNeighbour(nullptr), 
	chunkHeight(chunkHeight), 
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	init(false) {
	blockMatrix = new int**[chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		blockMatrix[i] = new int* [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			blockMatrix[i][j] = new int[chunkSideSize];
			for (int w = 0; w < chunkSideSize; w++) {
				blockMatrix[i][j][w] = 0;
			}
		}
	}
	size_t verticesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)120;
	size_t indicesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)36;
	vertices = new float[verticesMaxSize];
	indices = new int[indicesMaxSize];
}

Chunk::Chunk(int*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight), 
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	init(false) {
	this->blockMatrix = blockMatrix;
	size_t verticesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)120;
	size_t indicesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)36;
	vertices = new float[verticesMaxSize];
	indices = new int[indicesMaxSize];
}

void Chunk::renderingSetup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	init = true;
}

void Chunk::drawChunk() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, meshVertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Chunk::buildMesh() {
	if (!init)
		renderingSetup();
	
	int correctVertexCount = 0;
	int correctIndexCount = 0;
	int vertexIndexBase = 0;
	for (int i = 0; i < chunkHeight; i++) {
		for (int j = 0; j < chunkSideSize; j++) {
			for (int w = 0; w < chunkSideSize; w++) {
				if (blockMatrix[i][j][w] == 0) {
					continue;
				}
				float vertexBaseHeight = i - (blockSideSize / 2.0f);
				float vertexBaseWidth = j - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				float vertexBaseDepth = w - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				int vertexBaseIndex = correctVertexCount * 5;
				if ((i + 1) > (chunkHeight - 1) || blockMatrix[i + 1][j][w] == 0) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

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
				vertexBaseIndex = correctVertexCount * 5;
				if ((i - 1) < 0 || blockMatrix[i - 1][j][w] == 0) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

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
				vertexBaseIndex = correctVertexCount * 5;
				if (((j + 1) > (chunkSideSize - 1) && (findNeighbourBlock(NeighbourSide::RIGHT, i, j, w) == 0)) || ((j + 1) < chunkSideSize && blockMatrix[i][j + 1][w] == 0)) {
					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

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
				vertexBaseIndex = correctVertexCount * 5;
				if (((j - 1) < 0 && (findNeighbourBlock(NeighbourSide::LEFT, i, j, w) == 0)) || (((j - 1) >= 0) && blockMatrix[i][j - 1][w] == 0)) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

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
				vertexBaseIndex = correctVertexCount * 5;
				if (((w + 1) > (chunkSideSize - 1) && (findNeighbourBlock(NeighbourSide::FRONT, i, j, w) == 0)) || ((w + 1) < chunkSideSize && blockMatrix[i][j][w + 1] == 0)) {
					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

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
				vertexBaseIndex = correctVertexCount * 5;
				if (((w - 1) < 0 && (findNeighbourBlock(NeighbourSide::BACK, i, j, w) == 0)) || ((w - 1) >= 0 && blockMatrix[i][j][w - 1] == 0)) {
					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.28125f - textureOffset;
					vertices[vertexBaseIndex++] = 0.78125f + textureOffset;

					vertices[vertexBaseIndex++] = vertexBaseWidth + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseHeight + (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = vertexBaseDepth - (blockSideSize / 2.0f);
					vertices[vertexBaseIndex++] = 0.25f + textureOffset;
					vertices[vertexBaseIndex++] = 0.8125f - textureOffset;

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
	//std::cout << "Vertices " << correctVertexCount << std::endl;
	if (correctIndexCount > 0 && correctVertexCount > 2) {
		meshVertexCount = correctIndexCount;
		size_t vertexDataSize = (size_t)correctVertexCount * (size_t)5;
		verticesCompact = new float[vertexDataSize];
		indicesCompact = new int[meshVertexCount];
		for (int i = 0; i < vertexDataSize; i++) {
			verticesCompact[i] = vertices[i];
		}
		
		for (int i = 0; i < meshVertexCount; i++) {
			indicesCompact[i] = indices[i];
		}
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexDataSize, verticesCompact, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (meshVertexCount), indicesCompact, GL_STATIC_DRAW);
		glBindVertexArray(0);

		delete[] verticesCompact;
		delete[] indicesCompact;
		verticesCompact = nullptr;
		indicesCompact = nullptr;
	}
}

int Chunk::getBlockValue(int height, int width, int depth) {
	return blockMatrix[height][width][depth];
}

int Chunk::findNeighbourBlock(Chunk::NeighbourSide neighbourSide, int height, int width, int depth) {
	Chunk* neighbour = nullptr;
	switch (neighbourSide) {
	case NeighbourSide::LEFT:
		neighbour = leftNeighbour;
		width = chunkSideSize - 1;
		break;
	case NeighbourSide::RIGHT:
		neighbour = rightNeighbour;
		width = 0;
		break;
	case NeighbourSide::FRONT:
		neighbour = frontNeighbour;
		depth = 0;
		break;
	case NeighbourSide::BACK:
		neighbour = backNeighbour;
		depth = chunkSideSize - 1;
		break;
	}
	if (neighbour == nullptr) {
		return 0;
	}
	return neighbour->getBlockValue(height, width, depth);
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
	delete[] verticesCompact;
	delete[] indicesCompact;
	delete[] vertices;
	delete[] indices;
}

void Chunk::deleteChunkData(int*** chunkData, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete[] chunkData[i][j];
		}
		delete[] chunkData[i];
	}
	delete[] chunkData;
}