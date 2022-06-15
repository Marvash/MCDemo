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

void World::updateRenderableChunks() {
	m_chunkManager->updateRenderableChunks();
}

void World::updateGenerationOrigin(glm::vec3& position) {
	m_chunkManager->updateGenerationOrigin(position);
}

std::vector<ChunkRenderData*>* World::getRenderableChunks() {
	return m_chunkManager->getRenderableChunks();
}

void World::getCubesInRay(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength, std::vector<Cube*>& cubes) {
	m_chunkManager->getCubesInRay(rayOrigin, direction, rayLength, cubes);
}

void World::destroyBlock(Cube* toDestroy) {
	m_chunkManager->destroyBlock(toDestroy);
}

void World::placeBlock(Cube* toPlace, Cube::CubeId cubeId) {
	m_chunkManager->placeBlock(toPlace, cubeId);
}

void World::onNotify(Event& newEvent) {
}