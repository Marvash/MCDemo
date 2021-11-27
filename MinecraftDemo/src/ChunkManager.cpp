#include "ChunkManager.h"

const int ChunkManager::chunkArrayWidth = 24;
const int ChunkManager::chunkArrayDepth = 24;
const int ChunkManager::seaLevelOffset = 128;
const int ChunkManager::chunkSideSize = 16;
const int ChunkManager::chunkHeight = 256;
const int ChunkManager::nWorkers = 1;

ChunkManager::ChunkManager(glm::vec3 origin) : generationOrigin(origin), buildersShouldStop(false), generatorsShouldStop(false) {
	chunkMatrix = new Chunk ** [chunkArrayWidth];
	generationOrigin.y = 0.0f;
	playerPosition = generationOrigin;
	for (int i = 0; i < chunkArrayWidth; i++) {
		chunkMatrix[i] = new Chunk * [chunkArrayDepth];
		for (int j = 0; j < chunkArrayDepth; j++) {
			float xPos = generationOrigin.x + ((i - (chunkArrayWidth / 2)) * chunkSideSize) + (chunkSideSize / 2);
			float yPos = generationOrigin.y + (-seaLevelOffset);
			float zPos = generationOrigin.z + ((j - (chunkArrayDepth / 2)) * chunkSideSize) + (chunkSideSize / 2);
			glm::vec3 chunkPosition = glm::vec3(xPos, yPos, zPos);
			chunkMatrix[i][j] = new Chunk(chunkHeight, chunkSideSize, chunkPosition);
		}
	}
}

void ChunkManager::generateChunks() {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (generatorsShouldStop) {
				return;
			}
			internalLock.lock();
			if (chunkMatrix[i][j]->shouldRegenerate) {
				chunkMatrix[i][j]->shouldRegenerate = false;
				float xPos = generationOrigin.x + ((i - (chunkArrayWidth / 2)) * chunkSideSize) + (chunkSideSize / 2);
				float yPos = generationOrigin.y + (-seaLevelOffset);
				float zPos = generationOrigin.z + ((j - (chunkArrayDepth / 2)) * chunkSideSize) + (chunkSideSize / 2);
				Chunk* original = chunkMatrix[i][j];
				internalLock.unlock();
				glm::vec3 chunkPosition = glm::vec3(xPos, yPos, zPos);
				generateSingleChunk(chunkPosition, i, j, original);
			}
			else {
				internalLock.unlock();
			}
		}
	}
}

void ChunkManager::generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex, Chunk* original) {
	Cube**** blockMatrix = new Cube*** [chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		blockMatrix[i] = new Cube** [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			blockMatrix[i][j] = new Cube*[chunkSideSize];
			for (int w = 0; w < chunkSideSize; w++) {
				blockMatrix[i][j][w] = nullptr;
			}
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
					blockMatrix[i][j][w] = new Cube(Cube::CubeId::GRASS_BLOCK);
				}
				else {
					blockMatrix[i][j][w] = new Cube(Cube::CubeId::AIR_BLOCK);
				}
			}
		}
	}
	internalLock.lock();
	float xPos = generationOrigin.x + ((widthIndex - (chunkArrayWidth / 2)) * chunkSideSize) + (chunkSideSize / 2);
	float yPos = generationOrigin.y + (-seaLevelOffset);
	float zPos = generationOrigin.z + ((depthIndex - (chunkArrayDepth / 2)) * chunkSideSize) + (chunkSideSize / 2);
	Chunk* chunk = chunkMatrix[widthIndex][depthIndex];
	if (original == chunk && xPos == chunkPosition.x && yPos == chunkPosition.y && zPos == chunkPosition.z) {
		chunk->setBlockMatrix(blockMatrix);
		chunk->setPosition(chunkPosition);
		resetNeighbours();
		chunk->isMatrixUpdated = true;
		chunk->isMeshBuilt = false;
		chunk->isMeshLoaded = false;
		chunk->shouldRebuild = true;
		if (chunk->leftNeighbour != nullptr) {
			chunk->leftNeighbour->isMeshBuilt = false;
			chunk->leftNeighbour->isMeshLoaded = false;
			chunk->leftNeighbour->shouldRebuild = true;
		}
		if (chunk->rightNeighbour != nullptr) {
			chunk->rightNeighbour->isMeshBuilt = false;
			chunk->rightNeighbour->isMeshLoaded = false;
			chunk->rightNeighbour->shouldRebuild = true;
		}
		if (chunk->frontNeighbour != nullptr) {
			chunk->frontNeighbour->isMeshBuilt = false;
			chunk->frontNeighbour->isMeshLoaded = false;
			chunk->frontNeighbour->shouldRebuild = true;
		}
		if (chunk->backNeighbour != nullptr) {
			chunk->backNeighbour->isMeshBuilt = false;
			chunk->backNeighbour->isMeshLoaded = false;
			chunk->backNeighbour->shouldRebuild = true;
		}
	}
	else {
		original->shouldRegenerate = true;
		Chunk::deleteChunkData(blockMatrix, chunkHeight, chunkSideSize, chunkSideSize);
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

void ChunkManager::startBuilderThreads() {
	for (int i = 0; i < nWorkers; i++) {
		builderThreads.create_thread(boost::bind(&ChunkManager::builderThreadFunction, this));
	}
}

void ChunkManager::startGeneratorThreads() {
	for (int i = 0; i < nWorkers; i++) {
		generatorThreads.create_thread(boost::bind(&ChunkManager::generatorThreadFunction, this));
	}
}

void ChunkManager::startOriginUpdaterThreads() {
	for (int i = 0; i < nWorkers; i++) {
		originUpdaterThreads.create_thread(boost::bind(&ChunkManager::originUpdaterThreadFunction, this));
	}
}

void ChunkManager::generatorThreadFunction() {
	while (!generatorsShouldStop) {
		generateChunks();
	}
}

void ChunkManager::builderThreadFunction() {
	while (!buildersShouldStop) {
		rebuildChunks();
	}
}

void ChunkManager::originUpdaterThreadFunction() {
	while (!buildersShouldStop) {
		updateGenerationOrigin();
	}
}

void ChunkManager::reloadChunks() {
	int rebuiltChunks = 0;
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (rebuiltChunks > 0) {
				return;
			}
			internalLock.lock();
			if (!chunkMatrix[i][j]->isMeshLoaded && chunkMatrix[i][j]->isMeshBuilt && chunkMatrix[i][j]->isMatrixUpdated) {
				chunkMatrix[i][j]->loadMesh();
				chunkMatrix[i][j]->isMeshLoaded = true;
				rebuiltChunks++;
			}
			internalLock.unlock();
		}
	}
}

void ChunkManager::rebuildChunks() {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			if (buildersShouldStop) {
				return;
			}
			internalLock.lock();
			if (chunkMatrix[i][j]->shouldRebuild && chunkMatrix[i][j]->isMatrixUpdated) {
				chunkMatrix[i][j]->buildMesh();
				chunkMatrix[i][j]->shouldRebuild = false;
				chunkMatrix[i][j]->isMeshBuilt = true;
			}
			internalLock.unlock();
		}
	}
}

void ChunkManager::drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view) {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			internalLock.lock();
			if (chunkMatrix[i][j]->isMatrixUpdated && chunkMatrix[i][j]->isMeshLoaded) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, chunkMatrix[i][j]->chunkPosition);
				glm::mat4 mvp = projection * view * model * glm::mat4(1.0f);
				shader.setMat4("mvp", mvp);
				chunkMatrix[i][j]->drawChunk();
			}
			internalLock.unlock();
		}
	}
}

void ChunkManager::updatePlayerPosition(glm::vec3& playerPos) {
	internalLock.lock();
	playerPosition = playerPos;
	internalLock.unlock();
}

void ChunkManager::updateGenerationOrigin() {
	internalLock.lock();
	glm::vec3 quantizedPlayerPos = glm::vec3(((int(playerPosition.x)) / chunkSideSize) * chunkSideSize, 0.0f, ((int(playerPosition.z)) / chunkSideSize) * chunkSideSize);
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
	boost::this_thread::sleep_for(boost::chrono::milliseconds(33));
}

void ChunkManager::moveChunkMatrix(ChunkSide side) {
	Chunk** toMove = nullptr;
	switch (side) {
	case ChunkSide::RIGHT:
		toMove = new Chunk * [chunkArrayDepth];
		for (int i = 0; i < chunkArrayWidth; i++) {
			for (int j = 0; j < chunkArrayDepth; j++) {
				if (i == 0) {
					toMove[j] = chunkMatrix[i][j];
				}
				if (i != chunkArrayWidth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i + 1][j];
					if (i == 0) {
						chunkMatrix[i][j]->isMeshBuilt = false;
						chunkMatrix[i][j]->isMeshLoaded = false;
						chunkMatrix[i][j]->shouldRebuild = true;
					}
				}
				else {
					chunkMatrix[i][j] = toMove[j];
					chunkMatrix[i][j]->shouldRegenerate = true;
					chunkMatrix[i][j]->isMatrixUpdated = false;
				}
			}
		}
		break;
	case ChunkSide::LEFT:
		toMove = new Chunk * [chunkArrayDepth];
		for (int i = chunkArrayWidth - 1; i >= 0; i--) {
			for (int j = 0; j < chunkArrayDepth; j++) {
				if (i == (chunkArrayWidth - 1)) {
					toMove[j] = chunkMatrix[i][j];
				}
				if (i != 0) {
					chunkMatrix[i][j] = chunkMatrix[i - 1][j];
					if(i == (chunkArrayWidth - 1)) {
						chunkMatrix[i][j]->shouldRebuild = true;
						chunkMatrix[i][j]->isMeshBuilt = false;
						chunkMatrix[i][j]->isMeshLoaded = false;
					}
				}
				else {
					chunkMatrix[i][j] = toMove[j];
					chunkMatrix[i][j]->shouldRegenerate = true;
					chunkMatrix[i][j]->isMatrixUpdated = false;
				}
			}
		}
		break;
	case ChunkSide::BOTTOM:
		toMove = new Chunk * [chunkArrayWidth];
		for (int j = 0; j < chunkArrayDepth; j++) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == 0) {
					toMove[i] = chunkMatrix[i][j];
				}
				if (j != chunkArrayDepth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i][j + 1];
					if (j == 0) {
						chunkMatrix[i][j]->isMeshBuilt = false;
						chunkMatrix[i][j]->isMeshLoaded = false;
						chunkMatrix[i][j]->shouldRebuild = true;
					}
				}
				else {
					chunkMatrix[i][j] = toMove[i];
					chunkMatrix[i][j]->shouldRegenerate = true;
					chunkMatrix[i][j]->isMatrixUpdated = false;
				}
			}
		}
		break;
	case ChunkSide::TOP:
		toMove = new Chunk * [chunkArrayWidth];
		for (int j = chunkArrayDepth - 1; j >= 0; j--) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == (chunkArrayDepth - 1)) {
					toMove[i] = chunkMatrix[i][j];
				}
				if (j != 0) {
					chunkMatrix[i][j] = chunkMatrix[i][j - 1];
					if (j == chunkArrayDepth - 1) {
						chunkMatrix[i][j]->isMeshBuilt = false;
						chunkMatrix[i][j]->isMeshLoaded = false;
						chunkMatrix[i][j]->shouldRebuild = true;
					}
				}
				else {
					chunkMatrix[i][j] = toMove[i];
					chunkMatrix[i][j]->shouldRegenerate = true;
					chunkMatrix[i][j]->isMatrixUpdated = false;
				}
			}
		}
		break;
	}
}

ChunkManager::~ChunkManager() {
	buildersShouldStop = true;
	generatorsShouldStop = true;
	builderThreads.join_all();
	generatorThreads.join_all();
}