#include "World.h"

World::World(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_threadsRunning(false) {

}

void World::init(ChunkManager* chunkManager) {
	m_chunkManager = chunkManager;
}

void World::startThreads() {
	if (!m_threadsRunning) {
		m_chunkManager->startGeneratorThreads();
		m_chunkManager->startBuilderThreads();
		m_threadsRunning = !m_threadsRunning;
	}
}

void World::stopThreads() {
	if (m_threadsRunning) {
		m_chunkManager->stopGeneratorThreads();
		m_chunkManager->stopBuilderThreads();
		m_threadsRunning = !m_threadsRunning;
	}
}

void World::reloadChunks() {
	m_chunkManager->reloadChunks();
}

void World::updateGenerationOrigin(glm::vec3& position) {
	m_chunkManager->updateGenerationOrigin(position);
}

std::vector<RenderingComponent*>* World::getChunkComponents() {
	return m_chunkManager->getChunkRenderingComponents();
}

void World::getCubesInRay(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength, std::vector<Block*>& cubes) {
	m_chunkManager->getCubesInRay(rayOrigin, direction, rayLength, cubes);
}

Block* World::getCubeByCoords(glm::vec3 coords) {
	return m_chunkManager->getCubeByCoords(coords);
}

glm::vec3 World::getCubeAbsCoords(Block* cube) {
	return m_chunkManager->getCubeAbsCoords(cube);
}

void World::onNotify(Event& newEvent) {
}
