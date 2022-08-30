#include "ChunkManager.h"

const int ChunkManager::CHUNK_ARRAY_WIDTH = 24;
const int ChunkManager::CHUNK_ARRAY_DEPTH = 24;
const int ChunkManager::SEA_LEVEL_OFFSET = 128;
const int ChunkManager::CHUNK_SIDE_SIZE = 16;
const int ChunkManager::CHUNK_HEIGHT = 256;
const int ChunkManager::N_WORKERS_REBUILD = 1;
const int ChunkManager::N_WORKERS_REGEN = 4;

ChunkManager::ChunkManager(CoreEventDispatcher* eventDispatcher) :
	CoreService(eventDispatcher),
	m_generationOrigin(glm::vec3(0.0f, 0.0f, 0.0f)), 
	m_buildersShouldStop(false), 
	m_generatorsShouldStop(false),
	m_terrainGen(nullptr) {
	m_chunkMatrix = new Chunk ** [CHUNK_ARRAY_WIDTH];
	m_generationOrigin.y = 0.0f;
	m_playerPosition = m_generationOrigin;
	
}

void ChunkManager::init(BiomeLibrary* biomeManager, Atlas* atlas) {
	m_terrainGen = new TerrainGenerator(biomeManager, CHUNK_SIDE_SIZE, CHUNK_HEIGHT);
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		m_chunkMatrix[i] = new Chunk * [CHUNK_ARRAY_DEPTH];
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			float xPos = m_generationOrigin.x + ((i - (CHUNK_ARRAY_WIDTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
			float yPos = m_generationOrigin.y + (-SEA_LEVEL_OFFSET);
			float zPos = m_generationOrigin.z + ((j - (CHUNK_ARRAY_DEPTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
			//BOOST_LOG_TRIVIAL(info) << i << " " << j;
			//BOOST_LOG_TRIVIAL(info) << xPos << " " << yPos << " " << zPos;
			glm::vec3 chunkPosition = glm::vec3(xPos, yPos, zPos);
			m_chunkMatrix[i][j] = new Chunk(biomeManager, atlas, CHUNK_HEIGHT, CHUNK_SIDE_SIZE, chunkPosition);
			m_chunksRenderingComponents.push_back(m_chunkMatrix[i][j]->getRenderingComponent());
		}
	}
}

void ChunkManager::generateChunks() {
	static int counter = 0;
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			if (m_generatorsShouldStop) {
				return;
			}
			lockLP();
			if (m_chunkMatrix[i][j]->state == Chunk::ChunkState::SHOULDREGENERATE) {
				m_chunkMatrix[i][j]->state = Chunk::ChunkState::ISREGENERATING;
				float xPos = m_generationOrigin.x + ((i - (CHUNK_ARRAY_WIDTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
				float yPos = m_generationOrigin.y + (-SEA_LEVEL_OFFSET);
				float zPos = m_generationOrigin.z + ((j - (CHUNK_ARRAY_DEPTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
				Chunk* original = m_chunkMatrix[i][j];
				unlockLP();
				glm::vec3 chunkPosition = glm::vec3(xPos, yPos, zPos);
				generateSingleChunk(chunkPosition, i, j, original);
			}
			else {
				unlockLP();
			}
		}
	}
}

void ChunkManager::generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex, Chunk* chunk) {

	// Async terrain generation happens here
	Cube*** chunkBlockMatrix = chunk->getBlockMatrix();
	m_terrainGen->generateChunk(chunkBlockMatrix, chunkPosition);
	m_terrainGen->decorateChunk(chunkBlockMatrix, chunkPosition);

	lockLP();
	float xPos = m_generationOrigin.x + ((widthIndex - (CHUNK_ARRAY_WIDTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
	float yPos = m_generationOrigin.y + (-SEA_LEVEL_OFFSET);
	float zPos = m_generationOrigin.z + ((depthIndex - (CHUNK_ARRAY_DEPTH / 2)) * CHUNK_SIDE_SIZE) + (CHUNK_SIDE_SIZE / 2);
	//BOOST_LOG_TRIVIAL(info) << "x: " << xPos << " y: " << yPos << " z: " << zPos;
	Chunk* currentChunk = m_chunkMatrix[widthIndex][depthIndex];
	if (currentChunk == chunk && xPos == chunkPosition.x && yPos == chunkPosition.y && zPos == chunkPosition.z) {
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
		chunk->state = Chunk::ChunkState::SHOULDREGENERATE;
	}
	unlockLP();
}

void ChunkManager::resetNeighbours() {
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			if (m_chunkMatrix[i][j] != nullptr) {
				m_chunkMatrix[i][j]->leftNeighbour = nullptr;
				m_chunkMatrix[i][j]->rightNeighbour = nullptr;
				m_chunkMatrix[i][j]->backNeighbour = nullptr;
				m_chunkMatrix[i][j]->frontNeighbour = nullptr;
				if ((i - 1) >= 0) {
					m_chunkMatrix[i][j]->leftNeighbour = m_chunkMatrix[i - 1][j];
				}
				if ((i + 1) < CHUNK_ARRAY_WIDTH) {
					m_chunkMatrix[i][j]->rightNeighbour = m_chunkMatrix[i + 1][j];
				}
				if ((j - 1) >= 0) {
					m_chunkMatrix[i][j]->backNeighbour = m_chunkMatrix[i][j - 1];
				}
				if ((j + 1) < CHUNK_ARRAY_DEPTH) {
					m_chunkMatrix[i][j]->frontNeighbour = m_chunkMatrix[i][j + 1];
				}
			}
		}
	}
}

void ChunkManager::reloadChunks() {
	const int limit = 1;
	lockHP();
	int rebuiltChunks = 0;
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			// limiter
			if (rebuiltChunks > limit - 1) {
				unlockHP();
				return;
			}
			
			if (m_chunkMatrix[i][j]->state == Chunk::ChunkState::MESHBUILT) {
				m_chunkMatrix[i][j]->loadMesh();
				m_chunkMatrix[i][j]->state = Chunk::ChunkState::MESHLOADED;
				m_chunkMatrix[i][j]->canDraw = true;
				rebuiltChunks++;
			}
			//std::cout << m_chunkMatrix[i][j]->chunkPosition.x << " " << m_chunkMatrix[i][j]->chunkPosition.z << std::endl;
			
		}
	}
	unlockHP();
}

void ChunkManager::rebuildChunks() {
	lockLP();
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			if (m_buildersShouldStop) {
				unlockLP();
				return;
			}
			
			if (m_chunkMatrix[i][j]->state == Chunk::ChunkState::SHOULDREBUILD) {
				m_chunkMatrix[i][j]->buildMesh();
				m_chunkMatrix[i][j]->state = Chunk::ChunkState::MESHBUILT;
			}
			
		}
	}
	unlockLP();
}

void ChunkManager::updateRenderableChunks() {
	lockHP();
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			if (m_chunkMatrix[i][j]->state == Chunk::ChunkState::MESHLOADED || m_chunkMatrix[i][j]->canDraw) {
				 m_chunkMatrix[i][j]->getRenderingComponent()->m_enabled = true;
			}
		}
	}
	unlockHP();
}

std::vector<RenderingComponent*>* ChunkManager::getChunkRenderingComponents() {
	return &m_chunksRenderingComponents;
}

void ChunkManager::computeAdjacentCubes(Cube*** adjacentCubes, GameObject* gameObject, int radius) {
	if (radius < 1) {
		return;
	}
	int size = (radius * 2) + 1;
	glm::vec3 basePosition = gameObject->m_position;
	convertToCenteredCubeCoordinates(basePosition);
	glm::vec3 position;
	for (int h = 0; h < size; h++) {
		for (int w = 0; w < size; w++) {
			for (int d = 0; d < size; d++) {
				position.x = basePosition.x + float(w - int(size / 2.0f));
				position.y = basePosition.y + float(h - int(size / 2.0f));
				position.z = basePosition.z + float(d - int(size / 2.0f));
				Cube* cube = getCubeByCoords(position);
				if (cube != nullptr) {
					adjacentCubes[h][w][d] = *cube;
				}
				else {
					adjacentCubes[h][w][d] = Cube();
				}
			}
		}
	}
}

void ChunkManager::convertToCenteredCubeCoordinates(glm::vec3& coords) {
	coords.x = glm::floor(coords.x) + 0.5f;
	coords.y = glm::floor(coords.y) + 0.5f;
	coords.z = glm::floor(coords.z) + 0.5f;
}

glm::vec3 ChunkManager::getCubeAbsCoords(Cube* cube) {
	Chunk* chunk = cube->getChunkRef();
	int halfChunkSize = CHUNK_SIDE_SIZE / 2;
	if (chunk != nullptr) {
		return glm::vec3((chunk->chunkPosition.x - halfChunkSize) + cube->getCubeCoordsOffset().x, 
			chunk->chunkPosition.y + cube->getCubeCoordsOffset().y, 
			(chunk->chunkPosition.z - halfChunkSize) + cube->getCubeCoordsOffset().z);
	}
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

Cube* ChunkManager::solidBlockCast(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength) {
	std::vector<Cube*> cubes = getCubesInRay(rayOrigin, direction, rayLength);
	Cube* target = nullptr;
	if (cubes.size() > 0) {
		for (int i = 0; i < cubes.size(); i++) {
			if (cubes.at(i)->getCubeId() != CubeId::AIR_BLOCK && cubes.at(i)->getCubeId() != CubeId::UNGENERATED_BLOCK) {
				target = cubes.at(i);
				i = cubes.size();
			}
		}
	}
	return target;
}

void ChunkManager::destroyBlock(Cube* toDestroy) {
	lockLP();
	if (toDestroy != nullptr) {
		toDestroy->setCubeId(CubeId::AIR_BLOCK);
		Chunk* ownerChunk = toDestroy->getChunkRef();
		ownerChunk->buildMesh();
		ownerChunk->loadMesh();
		ownerChunk->state = Chunk::ChunkState::MESHLOADED;
		if (ownerChunk->leftNeighbour != nullptr) {
			ownerChunk->leftNeighbour->buildMesh();
			ownerChunk->leftNeighbour->loadMesh();
			ownerChunk->leftNeighbour->state = Chunk::ChunkState::MESHLOADED;
		}
		if (ownerChunk->rightNeighbour != nullptr) {
			ownerChunk->rightNeighbour->buildMesh();
			ownerChunk->rightNeighbour->loadMesh();
			ownerChunk->rightNeighbour->state = Chunk::ChunkState::MESHLOADED;
		}
		if (ownerChunk->frontNeighbour != nullptr) {
			ownerChunk->frontNeighbour->buildMesh();
			ownerChunk->frontNeighbour->loadMesh();
			ownerChunk->frontNeighbour->state = Chunk::ChunkState::MESHLOADED;
		}
		if (ownerChunk->backNeighbour != nullptr) {
			ownerChunk->backNeighbour->buildMesh();
			ownerChunk->backNeighbour->loadMesh();
			ownerChunk->backNeighbour->state = Chunk::ChunkState::MESHLOADED;
		}
	}
	unlockLP();
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
		if (toDestroy != nullptr && toDestroy->cubeId == CubeId::AIR_BLOCK) {
			toDestroy = nullptr;
		}
		currentIncrement += incrementStep;
	}
	if (toDestroy != nullptr) {
		toDestroy->setCubeId(CubeId::AIR_BLOCK);
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

void ChunkManager::placeBlock(Cube* toPlace, CubeId cubeId) {
	lockLP();
	if (toPlace != nullptr) {
		toPlace->setCubeId(cubeId);
		Chunk* ownerChunk = toPlace->getChunkRef();
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
	unlockLP();
}

Cube* ChunkManager::getCubeByCoords(glm::f64vec3 coords) {
	glm::f64vec3 originChunkPos = m_chunkMatrix[0][0]->chunkPosition;
	//BOOST_LOG_TRIVIAL(info) << originChunkPos.x << " " << originChunkPos.y << " " << originChunkPos.z;
	originChunkPos.x = originChunkPos.x - ((double)CHUNK_SIDE_SIZE / 2.0);
	originChunkPos.z = originChunkPos.z - ((double)CHUNK_SIDE_SIZE / 2.0);
	int chunkWidthIndex = glm::abs(int((coords.x - originChunkPos.x) / (double)CHUNK_SIDE_SIZE));
	int chunkDepthIndex = glm::abs(int((coords.z - originChunkPos.z) / (double)CHUNK_SIDE_SIZE));
	Chunk* tmp = m_chunkMatrix[chunkWidthIndex][chunkDepthIndex];
	//BOOST_LOG_TRIVIAL(info) << coords.x << " " << coords.y << " " << coords.z;
	Cube* cube = m_chunkMatrix[chunkWidthIndex][chunkDepthIndex]->getCubeByCoords(coords);
	return cube;
}

void ChunkManager::updateGenerationOrigin(glm::vec3& playerPos) {
	lockHP();
	m_playerPosition = playerPos;
	glm::vec3 quantizedPlayerPos = glm::vec3(((int(m_playerPosition.x)) / CHUNK_SIDE_SIZE) * CHUNK_SIDE_SIZE, 0.0f, ((int(m_playerPosition.z)) / CHUNK_SIDE_SIZE) * CHUNK_SIDE_SIZE);
	glm::vec3 diffVec = quantizedPlayerPos - m_generationOrigin;
	m_generationOrigin = quantizedPlayerPos;
	int xSteps = glm::abs(((int)(diffVec.x)) / CHUNK_SIDE_SIZE);
	int zSteps = glm::abs(((int)(diffVec.z)) / CHUNK_SIDE_SIZE);
	//BOOST_LOG_TRIVIAL(info) << "Moving default";
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
	unlockHP();
}

void ChunkManager::moveChunkMatrix(ChunkSide side) {
	Chunk** toMove = nullptr;
	switch (side) {
	case ChunkSide::RIGHT:
		toMove = new Chunk * [CHUNK_ARRAY_DEPTH];
		for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
			for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
				if (i == 0) {
					m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					m_chunkMatrix[i][j]->canDraw = false;
					toMove[j] = m_chunkMatrix[i][j];
					m_chunkMatrix[i][j] = m_chunkMatrix[i + 1][j];
					if(m_chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (i != CHUNK_ARRAY_WIDTH - 1) {
					m_chunkMatrix[i][j] = m_chunkMatrix[i + 1][j];
				} else {
					toMove[j]->chunkPosition = m_chunkMatrix[i][j]->chunkPosition;
					m_chunkMatrix[i][j] = toMove[j];
					m_chunkMatrix[i][j]->chunkPosition.x += CHUNK_SIDE_SIZE;
				}
			}
		}
		break;
	case ChunkSide::LEFT:
		toMove = new Chunk * [CHUNK_ARRAY_DEPTH];
		for (int i = CHUNK_ARRAY_WIDTH - 1; i >= 0; i--) {
			for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
				if (i == (CHUNK_ARRAY_WIDTH - 1)) {
					m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					m_chunkMatrix[i][j]->canDraw = false;
					toMove[j] = m_chunkMatrix[i][j];
					m_chunkMatrix[i][j] = m_chunkMatrix[i - 1][j];
					if (m_chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (i != 0) {
					m_chunkMatrix[i][j] = m_chunkMatrix[i - 1][j];
				} else {
					toMove[j]->chunkPosition = m_chunkMatrix[i][j]->chunkPosition;
					m_chunkMatrix[i][j] = toMove[j];
					m_chunkMatrix[i][j]->chunkPosition.x -= CHUNK_SIDE_SIZE;
				}
			}
		}
		break;
	case ChunkSide::BOTTOM:
		toMove = new Chunk * [CHUNK_ARRAY_WIDTH];
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
				if (j == 0) {
					m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					m_chunkMatrix[i][j]->canDraw = false;
					toMove[i] = m_chunkMatrix[i][j];
					m_chunkMatrix[i][j] = m_chunkMatrix[i][j + 1];
					if (m_chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (j != CHUNK_ARRAY_DEPTH - 1) {
					m_chunkMatrix[i][j] = m_chunkMatrix[i][j + 1];
				} else {
					toMove[i]->chunkPosition = m_chunkMatrix[i][j]->chunkPosition;
					m_chunkMatrix[i][j] = toMove[i];
					m_chunkMatrix[i][j]->chunkPosition.z += CHUNK_SIDE_SIZE;
				}
			}
		}
		break;
	case ChunkSide::TOP:
		toMove = new Chunk * [CHUNK_ARRAY_WIDTH];
		for (int j = CHUNK_ARRAY_DEPTH - 1; j >= 0; j--) {
			for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
				if (j == (CHUNK_ARRAY_DEPTH - 1)) {
					m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREGENERATE;
					m_chunkMatrix[i][j]->canDraw = false;
					toMove[i] = m_chunkMatrix[i][j];
					m_chunkMatrix[i][j] = m_chunkMatrix[i][j - 1];
					if (m_chunkMatrix[i][j]->state > Chunk::ChunkState::SHOULDREBUILD)
						m_chunkMatrix[i][j]->state = Chunk::ChunkState::SHOULDREBUILD;
				} else if (j != 0) {
					m_chunkMatrix[i][j] = m_chunkMatrix[i][j - 1];
				} else {
					toMove[i]->chunkPosition = m_chunkMatrix[i][j]->chunkPosition;
					m_chunkMatrix[i][j] = toMove[i];
					m_chunkMatrix[i][j]->chunkPosition.z -= CHUNK_SIDE_SIZE;
				}
			}
		}
		break;
	}
}

std::vector<Cube*> ChunkManager::getCubesInRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength) {
	glm::vec3 rayDirNorm = glm::normalize(rayDirection);
	float dor = glm::sqrt(rayDirNorm.x * rayDirNorm.x + rayDirNorm.z * rayDirNorm.z);
	float ym = rayDirNorm.y / dor;
	float zm = rayDirNorm.z / rayDirNorm.x;
	float dUnitx = glm::sqrt(1.0f + glm::pow(rayDirNorm.z / rayDirNorm.x, 2.0f));
	float dUnitz = glm::sqrt(glm::pow(rayDirNorm.x / rayDirNorm.z, 2.0f) + 1.0f);
	float xUnitStep = glm::sqrt(1.0f + glm::pow(ym * dUnitx, 2.0f) + glm::pow(zm, 2.0f));
	glm::vec3 xzRayDirNorm(glm::normalize(glm::vec3(rayDirNorm.x, 0.0f, rayDirNorm.z)));
	float yUnitStep = glm::sqrt(glm::pow((dor / rayDirNorm.y) * xzRayDirNorm.x, 2.0f) + 1.0f + glm::pow((dor / rayDirNorm.y) * xzRayDirNorm.z, 2.0f));
	float zUnitStep = glm::sqrt(glm::pow(rayDirNorm.x / rayDirNorm.z, 2.0f) + glm::pow(ym * dUnitz, 2.0f) + 1.0f);
	float xStep = 0.0f;
	float yStep = 0.0f;
	float zStep = 0.0f;
	float xRayLength = 0.0f;
	float yRayLength = 0.0f;
	float zRayLength = 0.0f;
	std::vector<Cube*> cubes;
	Cube* startingCube = getCubeByCoords(rayOrigin);
	if (startingCube != nullptr) {
		glm::vec3 startingCubePos = getCubeAbsCoords(startingCube);
		cubes.push_back(startingCube);
	}
	glm::vec3 originBlockCoords(glm::floor(rayOrigin.x), glm::floor(rayOrigin.y), glm::floor(rayOrigin.z));

	float mainAxisDelta = 0.0f;
	if (glm::sign(rayDirNorm.x) > 0.0f) {
		xStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.x - originBlockCoords.x);
	}
	else {
		xStep = -1.0f;
		mainAxisDelta = rayOrigin.x - originBlockCoords.x;
	}
	xRayLength = mainAxisDelta * xUnitStep;
	if (glm::sign(rayDirNorm.y) > 0.0f) {
		yStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.y - originBlockCoords.y);
	}
	else {
		yStep = -1.0f;
		mainAxisDelta = rayOrigin.y - originBlockCoords.y;
	}
	yRayLength = mainAxisDelta * yUnitStep;
	if (glm::sign(rayDirNorm.z) > 0.0f) {
		zStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.z - originBlockCoords.z);
	}
	else {
		zStep = -1.0f;
		mainAxisDelta = rayOrigin.z - originBlockCoords.z;
	}
	zRayLength = mainAxisDelta * zUnitStep;
	glm::vec3 nextCubePosition(getCubeAbsCoords(startingCube));
	float minDist = 0.0f;
	while (cubes.size() > 0 && minDist < rayLength) {
		if (xRayLength < yRayLength) {
			if (xRayLength < zRayLength) {
				minDist = xRayLength;
				xRayLength += xUnitStep;
				nextCubePosition.x += xStep;
			}
			else {
				minDist = zRayLength;
				zRayLength += zUnitStep;
				nextCubePosition.z += zStep;
			}
		}
		else if (yRayLength < zRayLength) {
			minDist = yRayLength;
			yRayLength += yUnitStep;
			nextCubePosition.y += yStep;
		}
		else {
			minDist = zRayLength;
			zRayLength += zUnitStep;
			nextCubePosition.z += zStep;
		}

		Cube* nextCube = getCubeByCoords(nextCubePosition);
		cubes.push_back(nextCube);
	}
	return cubes;
}

void ChunkManager::getCubesInRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength, std::vector<Cube*>& cubes) {
	glm::vec3 rayDirNorm = glm::normalize(rayDirection);
	float dor = glm::sqrt(rayDirNorm.x * rayDirNorm.x + rayDirNorm.z * rayDirNorm.z);
	float ym = rayDirNorm.y / dor;
	float zm = rayDirNorm.z / rayDirNorm.x;
	float dUnitx = glm::sqrt(1.0f + glm::pow(rayDirNorm.z / rayDirNorm.x, 2.0f));
	float dUnitz = glm::sqrt(glm::pow(rayDirNorm.x / rayDirNorm.z, 2.0f) + 1.0f);
	float xUnitStep = glm::sqrt(1.0f + glm::pow(ym * dUnitx, 2.0f) + glm::pow(zm, 2.0f));
	glm::vec3 xzRayDirNorm(glm::normalize(glm::vec3(rayDirNorm.x, 0.0f, rayDirNorm.z)));
	float yUnitStep = glm::sqrt(glm::pow((dor / rayDirNorm.y) * xzRayDirNorm.x, 2.0f) + 1.0f + glm::pow((dor / rayDirNorm.y) * xzRayDirNorm.z, 2.0f));
	float zUnitStep = glm::sqrt(glm::pow(rayDirNorm.x / rayDirNorm.z, 2.0f) + glm::pow(ym * dUnitz, 2.0f) + 1.0f);
	float xStep = 0.0f;
	float yStep = 0.0f;
	float zStep = 0.0f;
	float xRayLength = 0.0f;
	float yRayLength = 0.0f;
	float zRayLength = 0.0f;
	Cube* startingCube = getCubeByCoords(rayOrigin);
	if (startingCube != nullptr) {
		glm::vec3 startingCubePos = getCubeAbsCoords(startingCube);
		cubes.push_back(startingCube);
	}
	glm::vec3 originBlockCoords(glm::floor(rayOrigin.x), glm::floor(rayOrigin.y), glm::floor(rayOrigin.z));

	float mainAxisDelta = 0.0f;
	if (glm::sign(rayDirNorm.x) > 0.0f) {
		xStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.x - originBlockCoords.x);
	}
	else {
		xStep = -1.0f;
		mainAxisDelta = rayOrigin.x - originBlockCoords.x;
	}
	xRayLength = mainAxisDelta * xUnitStep;
	if (glm::sign(rayDirNorm.y) > 0.0f) {
		yStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.y - originBlockCoords.y);
	}
	else {
		yStep = -1.0f;
		mainAxisDelta = rayOrigin.y - originBlockCoords.y;
	}
	yRayLength = mainAxisDelta * yUnitStep;
	if (glm::sign(rayDirNorm.z) > 0.0f) {
		zStep = 1.0f;
		mainAxisDelta = 1.0f - (rayOrigin.z - originBlockCoords.z);
	}
	else {
		zStep = -1.0f;
		mainAxisDelta = rayOrigin.z - originBlockCoords.z;
	}
	zRayLength = mainAxisDelta * zUnitStep;
	glm::vec3 nextCubePosition(getCubeAbsCoords(startingCube));
	float minDist = 0.0f;
	while (cubes.size() > 0 && minDist < rayLength) {
		if (xRayLength < yRayLength) {
			if (xRayLength < zRayLength) {
				minDist = xRayLength;
				xRayLength += xUnitStep;
				nextCubePosition.x += xStep;
			}
			else {
				minDist = zRayLength;
				zRayLength += zUnitStep;
				nextCubePosition.z += zStep;
			}
		}
		else if (yRayLength < zRayLength) {
			minDist = yRayLength;
			yRayLength += yUnitStep;
			nextCubePosition.y += yStep;
		}
		else {
			minDist = zRayLength;
			zRayLength += zUnitStep;
			nextCubePosition.z += zStep;
		}

		Cube* nextCube = getCubeByCoords(nextCubePosition);
		cubes.push_back(nextCube);
	}
}

void ChunkManager::lockHP() {
	m_internalLockNext.lock();
	m_internalLockData.lock();
	m_internalLockNext.unlock();
}
void ChunkManager::unlockHP() {
	m_internalLockData.unlock();
}
void ChunkManager::lockLP() {
	m_internalLockLP.lock();
	m_internalLockNext.lock();
	m_internalLockData.lock();
	m_internalLockNext.unlock();
}
void ChunkManager::unlockLP() {
	m_internalLockData.unlock();
	m_internalLockLP.unlock();
}

void ChunkManager::startBuilderThreads() {
	for (int i = 0; i < N_WORKERS_REBUILD; i++) {
		m_builderThreads.create_thread(boost::bind(&ChunkManager::builderThreadFunction, this));
	}
}

void ChunkManager::startGeneratorThreads() {
	for (int i = 0; i < N_WORKERS_REGEN; i++) {
		m_generatorThreads.create_thread(boost::bind(&ChunkManager::generatorThreadFunction, this));
	}
}

void ChunkManager::stopBuilderThreads() {
	m_buildersShouldStop = true;
	m_builderThreads.join_all();
}

void ChunkManager::stopGeneratorThreads() {
	m_generatorsShouldStop = true;
	m_generatorThreads.join_all();
}

void ChunkManager::generatorThreadFunction() {
	while (!m_generatorsShouldStop) {
		generateChunks();
	}
}

void ChunkManager::builderThreadFunction() {
	while (!m_buildersShouldStop) {
		rebuildChunks();
	}
}

ChunkManager::~ChunkManager() {
	stopGeneratorThreads();
	stopBuilderThreads();
}

void ChunkManager::onNotify(Event& newEvent) {

}

void ChunkManager::notify(Event& newEvent) {

}