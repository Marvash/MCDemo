#include "ChunkManager.h"

const int ChunkManager::chunkArrayWidth = 24;
const int ChunkManager::chunkArrayDepth = 24;
const int ChunkManager::seaLevelOffset = 128;
const int ChunkManager::chunkSideSize = 16;
const int ChunkManager::chunkHeight = 256;

ChunkManager::ChunkManager(glm::vec3 origin) : generationOrigin(origin), builderShouldStop(false) {
	chunkMatrix = new Chunk ** [chunkArrayWidth];
	rebuildMatrix = new bool* [chunkArrayWidth];
	for (int i = 0; i < chunkArrayWidth; i++) {
		chunkMatrix[i] = new Chunk*[chunkArrayDepth];
		rebuildMatrix[i] = new bool[chunkArrayDepth];
		for (int j = 0; j < chunkArrayDepth; j++) {
			chunkMatrix[i][j] = nullptr;
			rebuildMatrix[i][j] = false;
		}
	}
	generationOrigin.y = 0.0f;
}

void ChunkManager::generateChunks() {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (builderShouldStop) {
				return;
			}
			if (chunkMatrix[i][j] == nullptr) {
				internalLock.lock();
				float xPos = generationOrigin.x + ((i - (chunkArrayWidth / 2)) * chunkSideSize) + (chunkSideSize / 2);
				float yPos = generationOrigin.y + (-seaLevelOffset);
				float zPos = generationOrigin.z + ((j - (chunkArrayDepth / 2)) * chunkSideSize) + (chunkSideSize / 2);
				internalLock.unlock();
				glm::vec3 chunkPosition = glm::vec3(xPos, yPos, zPos);
				generateSingleChunk(chunkPosition, i, j);
			}
		}
	}
}

void ChunkManager::generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex) {
	int*** blockMatrix = new int** [chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		blockMatrix[i] = new int* [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			blockMatrix[i][j] = new int[chunkSideSize];
		}
	}
	for (int j = 0; j < chunkSideSize; j++) {
		for (int w = 0; w < chunkSideSize; w++) {
			float baseWidth = chunkPosition.x + ((j - (chunkSideSize / 2)) - 0.5f);
			float baseDepth = chunkPosition.z + ((w - (chunkSideSize / 2)) - 0.5f);
			int height = 100;
			int terrainHeight = 90;
			float amplitude = 50.0f;
			int perlinFrequency = 256;
			for (int i = 0; i < 4; i++) {
				height += (int)perlinGen.getValue(baseWidth, baseDepth, perlinFrequency, amplitude);
				amplitude = amplitude / 2.0f;
				perlinFrequency = perlinFrequency / 2;
			}
			for (int i = 0; i < chunkHeight; i++) {
				if (i >= 0 && i < height) {
					blockMatrix[i][j][w] = 1;
				}
				else {
					blockMatrix[i][j][w] = 0;
				}
			}
		}
	}
	internalLock.lock();
	float xPos = generationOrigin.x + ((widthIndex - (chunkArrayWidth / 2)) * chunkSideSize) + (chunkSideSize / 2);
	float yPos = generationOrigin.y + (-seaLevelOffset);
	float zPos = generationOrigin.z + ((depthIndex - (chunkArrayDepth / 2)) * chunkSideSize) + (chunkSideSize / 2);
	if (xPos == chunkPosition.x && yPos == chunkPosition.y && zPos == chunkPosition.z) {
		chunkMatrix[widthIndex][depthIndex] = new Chunk(blockMatrix, chunkHeight, chunkSideSize, chunkPosition);
		resetNeighbours();
		Chunk* chunk = chunkMatrix[widthIndex][depthIndex];
		rebuildMatrix[widthIndex][depthIndex] = true;
		if (chunk->leftNeighbour != nullptr) {
			rebuildMatrix[widthIndex-1][depthIndex] = true;
		}
		if (chunk->rightNeighbour != nullptr) {
			rebuildMatrix[widthIndex+1][depthIndex] = true;
		}
		if (chunk->frontNeighbour != nullptr) {
			rebuildMatrix[widthIndex][depthIndex+1] = true;
		}
		if (chunk->backNeighbour != nullptr) {
			rebuildMatrix[widthIndex][depthIndex-1] = true;
		}
	}
	else {
		Chunk::deleteChunkData(blockMatrix, chunkHeight, chunkSideSize);
	}
	internalLock.unlock();
}

void ChunkManager::resetNeighbours() {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (chunkMatrix[i][j] != nullptr) {
				chunkMatrix[i][j]->leftNeighbour = nullptr;
				chunkMatrix[i][j]->rightNeighbour = nullptr;
				chunkMatrix[i][j]->backNeighbour = nullptr;
				chunkMatrix[i][j]->frontNeighbour = nullptr;
				if ((i - 1) >= 0) {
					chunkMatrix[i][j]->leftNeighbour = chunkMatrix[i - 1][j];
				}
				if ((i + 1) < chunkArrayWidth) {
					chunkMatrix[i][j]->rightNeighbour = chunkMatrix[i + 1][j];
				}
				if ((j - 1) >= 0) {
					chunkMatrix[i][j]->backNeighbour = chunkMatrix[i][j - 1];
				}
				if ((j + 1) < chunkArrayDepth) {
					chunkMatrix[i][j]->frontNeighbour = chunkMatrix[i][j + 1];
				}
			}
		}
	}
}

void ChunkManager::startBuilderThread() {
	builderThread = boost::thread(boost::bind(&ChunkManager::builderThreadFunction, this));
}

void ChunkManager::builderThreadFunction() {
	while (!builderShouldStop) {
		generateChunks();
	}
}

void ChunkManager::rebuildChunks() {
	internalLock.lock();
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (rebuildMatrix[i][j]) {
				if (chunkMatrix[i][j] != nullptr) {
					chunkMatrix[i][j]->buildMesh();
				}
				rebuildMatrix[i][j] = false;
			}
		}
	}
	internalLock.unlock();
}

void ChunkManager::drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view) {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (chunkMatrix[i][j] != nullptr) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, chunkMatrix[i][j]->chunkPosition);
				glm::mat4 mvp = projection * view * model * glm::mat4(1.0f);
				shader.setMat4("mvp", mvp);
				chunkMatrix[i][j]->drawChunk();
			}
		}
	}
}

void ChunkManager::updateGenerationOrigin(glm::vec3& playerPos) {
	internalLock.lock();
	glm::vec3 quantizedPlayerPos = glm::vec3(((int(playerPos.x)) / chunkSideSize) * chunkSideSize, 0.0f, ((int(playerPos.z)) / chunkSideSize) * chunkSideSize);
	glm::vec3 diffVec = quantizedPlayerPos - generationOrigin;
	generationOrigin = quantizedPlayerPos;
	int xSteps = glm::abs(((int)(diffVec.x)) / chunkSideSize);
	int zSteps = glm::abs(((int)(diffVec.z)) / chunkSideSize);
	if (diffVec.x > 0.0f) {
		for (int i = 0; i < xSteps; i++) {
			moveChunkMatrix(ChunkSide::RIGHT);
		}
	}
	if (diffVec.x < 0.0f) {
		for (int i = 0; i < xSteps; i++) {
			moveChunkMatrix(ChunkSide::LEFT);
		}
	}
	if (diffVec.z > 0.0f) {
		for (int i = 0; i < zSteps; i++) {
			moveChunkMatrix(ChunkSide::BOTTOM);
		}
	}
	if (diffVec.z < 0.0f) {
		for (int i = 0; i < zSteps; i++) {
			moveChunkMatrix(ChunkSide::TOP);
		}
	}
	resetNeighbours();
	internalLock.unlock();
}

void ChunkManager::moveChunkMatrix(ChunkSide side) {
	int deleted = 0;
	switch (side) {
	case ChunkSide::RIGHT:
		for (int i = 0; i < chunkArrayWidth; i++) {
			for (int j = 0; j < chunkArrayDepth; j++) {
				if (i == 0 && chunkMatrix[i][j] != nullptr) {
					delete chunkMatrix[i][j];
					deleted++;
					rebuildMatrix[i][j] = true;
				}
				if (i != chunkArrayWidth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i + 1][j];
					if(i != 0)
						rebuildMatrix[i][j] = rebuildMatrix[i + 1][j];
				}
				else {
					chunkMatrix[i][j] = nullptr;
					rebuildMatrix[i - 1][j] = false;
				}
			}
		}
		break;
	case ChunkSide::LEFT:
		for (int i = chunkArrayWidth - 1; i >= 0; i--) {
			for (int j = 0; j < chunkArrayDepth; j++) {
				if (i == (chunkArrayWidth - 1) && chunkMatrix[i][j] != nullptr) {
					delete chunkMatrix[i][j];
					deleted++;
					rebuildMatrix[i][j] = true;
				}
				if (i != 0) {
					chunkMatrix[i][j] = chunkMatrix[i - 1][j];
					if (i != chunkArrayWidth - 1)
						rebuildMatrix[i][j] = rebuildMatrix[i - 1][j];
				}
				else {
					chunkMatrix[i][j] = nullptr;
					rebuildMatrix[i + 1][j] = true;
				}
			}
		}
		break;
	case ChunkSide::BOTTOM:
		for (int j = 0; j < chunkArrayDepth; j++) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == 0 && chunkMatrix[i][j] != nullptr) {
					delete chunkMatrix[i][j];
					deleted++;
					rebuildMatrix[i][j] = true;
				}
				if (j != chunkArrayDepth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i][j + 1];
					if (j != 0)
						rebuildMatrix[i][j] = rebuildMatrix[i][j + 1];
				}
				else {
					chunkMatrix[i][j] = nullptr;
					rebuildMatrix[i][j - 1] = false;
				}
			}
		}
		break;
	case ChunkSide::TOP:
		for (int j = chunkArrayDepth - 1; j >= 0; j--) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == (chunkArrayDepth - 1) && chunkMatrix[i][j] != nullptr) {
					delete chunkMatrix[i][j];
					deleted++;
					rebuildMatrix[i][j] = true;
				}
				if (j != 0) {
					chunkMatrix[i][j] = chunkMatrix[i][j - 1];
					if (j != chunkArrayDepth - 1)
						rebuildMatrix[i][j] = rebuildMatrix[i][j - 1];
				}
				else {
					chunkMatrix[i][j] = nullptr;
					rebuildMatrix[i][j + 1] = false;
				}
			}
		}
		break;
	}
}

ChunkManager::~ChunkManager() {
	builderShouldStop = true;
	builderThread.join();
}