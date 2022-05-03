#include "ChunkManager.h"
#include "Core/Services/CoreServiceLocator.h"

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

void ChunkManager::init(BiomeManager* biomeManager, Atlas* atlas) {
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
	m_renderableChunks.clear();
	lockHP();
	for (int i = 0; i < CHUNK_ARRAY_WIDTH; i++) {
		for (int j = 0; j < CHUNK_ARRAY_DEPTH; j++) {
			if (m_chunkMatrix[i][j]->state == Chunk::ChunkState::MESHLOADED || m_chunkMatrix[i][j]->canDraw) {
				 m_renderableChunks.push_back(&m_chunkMatrix[i][j]->getChunkRenderData());
			}
		}
	}
	unlockHP();
}

std::vector<ChunkRenderData*>* ChunkManager::getRenderableChunks() {
	return &m_renderableChunks;
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
				lockHP();
				Cube* cube = getCubeByCoords(position);
				if (cube != nullptr) {
					adjacentCubes[h][w][d] = *getCubeByCoords(position);
				}
				else {
					adjacentCubes[h][w][d] = Cube(Cube::CubeId::UNGENERATED_BLOCK, nullptr, nullptr);
				}
				unlockHP();
			}
		}
	}
}

void ChunkManager::convertToCenteredCubeCoordinates(glm::vec3& coords) {
	coords.x = glm::floor(coords.x) + 0.5f;
	coords.y = glm::floor(coords.y) + 0.5f;
	coords.z = glm::floor(coords.z) + 0.5f;
}

void ChunkManager::destroyBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection) {
	float rayLength = 10.0f;
	lockLP();
	std::vector<Cube*> cubes = RayCast::castRay(this, rayOrigin, playerLookDirection, rayLength);
	Cube* toDestroy = nullptr;
	if (cubes.size() > 0) {
		for (int i = 0; i < cubes.size(); i++) {
			if (cubes.at(i)->getCubeId() != Cube::CubeId::AIR_BLOCK) {
				toDestroy = cubes.at(i);
				i = cubes.size();
			}
		}
	}
	if (toDestroy != nullptr) {
		toDestroy->setCubeId(Cube::CubeId::AIR_BLOCK);
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

void ChunkManager::placeBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection, Cube::CubeId cubeId) {
	float rayLength = 10.0f;
	lockLP();
	std::vector<Cube*> cubes = RayCast::castRay(this, rayOrigin, playerLookDirection, rayLength);
	Cube* toFill = nullptr;
	if (cubes.size() > 0) {
		for (int i = 0; i < cubes.size(); i++) {
			if (i > 0 && cubes.at(i)->getCubeId() != Cube::CubeId::AIR_BLOCK) {
				toFill = cubes.at(i - 1);
				i = cubes.size();
			}
		}
	}
	if (toFill != nullptr) {
		toFill->setCubeId(cubeId);
		Chunk* ownerChunk = toFill->getChunkRef();
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

Cube* ChunkManager::getCubeByCoords(glm::vec3 coords) {
	glm::vec3 originChunkPos = m_chunkMatrix[0][0]->chunkPosition;
	//BOOST_LOG_TRIVIAL(info) << originChunkPos.x << " " << originChunkPos.y << " " << originChunkPos.z;
	originChunkPos.x = originChunkPos.x - (CHUNK_SIDE_SIZE / 2.0f);
	originChunkPos.z = originChunkPos.z - (CHUNK_SIDE_SIZE / 2.0f);
	int chunkWidthIndex = glm::abs(int((coords.x - originChunkPos.x) / CHUNK_SIDE_SIZE));
	int chunkDepthIndex = glm::abs(int((coords.z - originChunkPos.z) / CHUNK_SIDE_SIZE));
	Chunk* tmp = m_chunkMatrix[chunkWidthIndex][chunkDepthIndex];
	//BOOST_LOG_TRIVIAL(info) << coords.x << " " << coords.y << " " << coords.z;
	return m_chunkMatrix[chunkWidthIndex][chunkDepthIndex]->getCubeByCoords(coords);
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