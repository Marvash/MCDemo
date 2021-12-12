#include "ChunkManager.h"

const int ChunkManager::chunkArrayWidth = 24;
const int ChunkManager::chunkArrayDepth = 24;
const int ChunkManager::seaLevelOffset = 128;
const int ChunkManager::chunkSideSize = 16;
const int ChunkManager::chunkHeight = 256;
const int ChunkManager::nWorkersRebuild = 1;
const int ChunkManager::nWorkersRegen = 1;
const int ChunkManager::nWorkersUpdate = 1;

ChunkManager::ChunkManager(glm::vec3 origin) : generationOrigin(origin), buildersShouldStop(false), generatorsShouldStop(false), updaterShouldStop(false) {
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
			if (chunkMatrix[i][j]->state == Chunk::ChunkState::SHOULDREGENERATE) {
				chunkMatrix[i][j]->state = Chunk::ChunkState::ISREGENERATING;
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
	Cube*** blockMatrix = new Cube** [chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		blockMatrix[i] = new Cube* [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			blockMatrix[i][j] = new Cube[chunkSideSize];
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
			int dirtHeight = 70;
			for (int i = 0; i < chunkHeight; i++) {
				if (i <= height) {
					if (i < dirtHeight) {
						blockMatrix[i][j][w] = Cube(Cube::CubeId::STONE_BLOCK, original);
					}
					else if (i >= dirtHeight && i < height) {
						blockMatrix[i][j][w] = Cube(Cube::CubeId::DIRT_BLOCK, original);
					}
					else if (i == height) {
						blockMatrix[i][j][w] = Cube(Cube::CubeId::GRASS_BLOCK, original);
					}
				}
				else {
					blockMatrix[i][j][w] = Cube(Cube::CubeId::AIR_BLOCK, original);
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
		chunk->state = Chunk::ChunkState::SHOULDREBUILD;
		if (chunk->leftNeighbour != nullptr && chunk->leftNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			chunk->leftNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (chunk->rightNeighbour != nullptr && chunk->rightNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			chunk->rightNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (chunk->frontNeighbour != nullptr && chunk->frontNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			chunk->frontNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (chunk->backNeighbour != nullptr && chunk->backNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			chunk->backNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
	}
	else {
		original->state = Chunk::ChunkState::SHOULDREGENERATE;
		Chunk::deleteChunkData(blockMatrix, chunkHeight, chunkSideSize);
	}
	internalLock.unlock();
}

void destroyBlock() {

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
	for (int i = 0; i < nWorkersRebuild; i++) {
		builderThreads.create_thread(boost::bind(&ChunkManager::builderThreadFunction, this));
	}
}

void ChunkManager::startGeneratorThreads() {
	for (int i = 0; i < nWorkersRegen; i++) {
		generatorThreads.create_thread(boost::bind(&ChunkManager::generatorThreadFunction, this));
	}
}

void ChunkManager::startOriginUpdaterThreads() {
	for (int i = 0; i < nWorkersUpdate; i++) {
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
	while (!updaterShouldStop) {
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
			if (chunkMatrix[i][j]->state == Chunk::ChunkState::MESHBUILT) {
				chunkMatrix[i][j]->loadMesh();
				chunkMatrix[i][j]->state = Chunk::ChunkState::MESHLOADED;
				chunkMatrix[i][j]->canDraw = true;
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
			if (chunkMatrix[i][j]->state == Chunk::ChunkState::SHOULDREBUILD) {
				chunkMatrix[i][j]->buildMesh();
				chunkMatrix[i][j]->state = Chunk::ChunkState::MESHBUILT;
				
			}
			internalLock.unlock();
		}
	}
}

void ChunkManager::drawChunks(Shader& shader, glm::mat4& projection, glm::mat4& view) {
	for (int i = 0; i < chunkArrayWidth; i++) {
		for (int j = 0; j < chunkArrayDepth; j++) {
			internalLock.lock();
			if (chunkMatrix[i][j]->state >= Chunk::ChunkState::MESHLOADED || chunkMatrix[i][j]->canDraw) {
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

void ChunkManager::destroyBlock() {
	float rayLength = 10.0f;
	internalLock.lock();
	std::vector<Cube*> cubes = RayCast::castRay(this, playerPosition, playerLookDirection, rayLength);
	Cube* toDestroy = nullptr;
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes.at(i)->cubeId != Cube::CubeId::AIR_BLOCK) {
			toDestroy = cubes.at(i);
			i = cubes.size();
		}
	}
	if (toDestroy != nullptr) {
		toDestroy->setCubeId(Cube::CubeId::AIR_BLOCK);
		Chunk* ownerChunk = toDestroy->chunkRef;
		ownerChunk->state = Chunk::ChunkState::SHOULDREBUILD;
		if (ownerChunk->leftNeighbour != nullptr && ownerChunk->leftNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->leftNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->rightNeighbour != nullptr && ownerChunk->rightNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->rightNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->frontNeighbour != nullptr && ownerChunk->frontNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->frontNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->backNeighbour != nullptr && ownerChunk->backNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->backNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
	}
	internalLock.unlock();
	//Naive solution (ray marching)
	/*
	glm::vec3 rayEnd = playerPosition;
	float currentIncrement = 0.0f;
	float incrementStep = 0.1f;
	Cube* toDestroy = nullptr;
	internalLock.lock();
	while (toDestroy == nullptr && glm::length(rayEnd - playerPosition) < rayLength) {
		rayEnd = playerPosition + (playerLookDirection * currentIncrement);
		toDestroy = getCubeByCoords(rayEnd);
		if (toDestroy != nullptr && toDestroy->cubeId == Cube::CubeId::AIR_BLOCK) {
			toDestroy = nullptr;
		}
		currentIncrement += incrementStep;
	}
	if (toDestroy != nullptr) {
		toDestroy->setCubeId(Cube::CubeId::AIR_BLOCK);
		Chunk* ownerChunk = toDestroy->chunkRef;
		ownerChunk->state = Chunk::ChunkState::SHOULDREBUILD;
		if (ownerChunk->leftNeighbour != nullptr && ownerChunk->leftNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->leftNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->rightNeighbour != nullptr && ownerChunk->rightNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->rightNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->frontNeighbour != nullptr && ownerChunk->frontNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->frontNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->backNeighbour != nullptr && ownerChunk->backNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->backNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
	}
	internalLock.unlock();
	*/
}

void ChunkManager::placeBlock(Cube::CubeId cubeId) {
	float rayLength = 10.0f;
	internalLock.lock();
	std::vector<Cube*> cubes = RayCast::castRay(this, playerPosition, playerLookDirection, rayLength);
	Cube* toFill = nullptr;
	for (int i = 0; i < cubes.size(); i++) {
		if (i > 0 && cubes.at(i)->cubeId != Cube::CubeId::AIR_BLOCK) {
			toFill = cubes.at(i - 1);
			i = cubes.size();
		}
	}
	if (toFill != nullptr) {
		toFill->setCubeId(cubeId);
		Chunk* ownerChunk = toFill->chunkRef;
		ownerChunk->state = Chunk::ChunkState::SHOULDREBUILD;
		if (ownerChunk->leftNeighbour != nullptr && ownerChunk->leftNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->leftNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->rightNeighbour != nullptr && ownerChunk->rightNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->rightNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->frontNeighbour != nullptr && ownerChunk->frontNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->frontNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
		if (ownerChunk->backNeighbour != nullptr && ownerChunk->backNeighbour->state > Chunk::ChunkState::SHOULDREBUILD) {
			ownerChunk->backNeighbour->state = Chunk::ChunkState::SHOULDREBUILD;
		}
	}
	internalLock.unlock();
}

Cube* ChunkManager::getCubeByCoords(glm::vec3& coords) {
	glm::vec3 originChunkPos = chunkMatrix[0][0]->chunkPosition;
	originChunkPos.x = originChunkPos.x - (chunkSideSize / 2.0f);
	originChunkPos.z = originChunkPos.z - (chunkSideSize / 2.0f);
	int chunkWidthIndex = glm::abs(glm::floor((coords.x - originChunkPos.x) / chunkSideSize));
	int chunkDepthIndex = glm::abs(glm::floor((coords.z - originChunkPos.z) / chunkSideSize));
	return chunkMatrix[chunkWidthIndex][chunkDepthIndex]->getCubeByCoords(coords);
}

void ChunkManager::updatePlayerData(glm::vec3& playerPos, glm::vec3& playerLookDir) {
	internalLock.lock();
	playerPosition = playerPos;
	playerLookDirection = playerLookDir;
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
					chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					chunkMatrix[i][j]->canDraw = false;
					toMove[j] = chunkMatrix[i][j];
					chunkMatrix[i][j] = chunkMatrix[i + 1][j];
					if(chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (i != chunkArrayWidth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i + 1][j];
				} else {
					chunkMatrix[i][j] = toMove[j];
				}
			}
		}
		break;
	case ChunkSide::LEFT:
		toMove = new Chunk * [chunkArrayDepth];
		for (int i = chunkArrayWidth - 1; i >= 0; i--) {
			for (int j = 0; j < chunkArrayDepth; j++) {
				if (i == (chunkArrayWidth - 1)) {
					chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					chunkMatrix[i][j]->canDraw = false;
					toMove[j] = chunkMatrix[i][j];
					chunkMatrix[i][j] = chunkMatrix[i - 1][j];
					if (chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (i != 0) {
					chunkMatrix[i][j] = chunkMatrix[i - 1][j];
				} else {
					chunkMatrix[i][j] = toMove[j];
				}
			}
		}
		break;
	case ChunkSide::BOTTOM:
		toMove = new Chunk * [chunkArrayWidth];
		for (int j = 0; j < chunkArrayDepth; j++) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == 0) {
					chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					chunkMatrix[i][j]->canDraw = false;
					toMove[i] = chunkMatrix[i][j];
					chunkMatrix[i][j] = chunkMatrix[i][j + 1];
					if (chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (j != chunkArrayDepth - 1) {
					chunkMatrix[i][j] = chunkMatrix[i][j + 1];
				} else {
					chunkMatrix[i][j] = toMove[i];
				}
			}
		}
		break;
	case ChunkSide::TOP:
		toMove = new Chunk * [chunkArrayWidth];
		for (int j = chunkArrayDepth - 1; j >= 0; j--) {
			for (int i = 0; i < chunkArrayWidth; i++) {
				if (j == (chunkArrayDepth - 1)) {
					chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					chunkMatrix[i][j]->canDraw = false;
					toMove[i] = chunkMatrix[i][j];
					chunkMatrix[i][j] = chunkMatrix[i][j - 1];
					if (chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (j != 0) {
					chunkMatrix[i][j] = chunkMatrix[i][j - 1];
				} else {
					chunkMatrix[i][j] = toMove[i];
				}
			}
		}
		break;
	}
}

ChunkManager::~ChunkManager() {
	buildersShouldStop = true;
	generatorsShouldStop = true;
	updaterShouldStop = true;
	builderThreads.join_all();
	generatorThreads.join_all();
	originUpdaterThreads.join_all();
}