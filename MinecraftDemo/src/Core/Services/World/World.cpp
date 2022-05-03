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

std::vector<ChunkRenderData*>* World::getRenderableChunks() {
	return m_chunkManager->getRenderableChunks();
}

void World::destroyBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection) {
	m_chunkManager->destroyBlock(rayOrigin, playerLookDirection);
}

void World::placeBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection, Cube::CubeId cubeId) {
	m_chunkManager->placeBlock(rayOrigin, playerLookDirection, cubeId);
}

void World::onNotify(Event& newEvent) {
	switch (newEvent.getEventType()) {
		case EventType::PLAYER_MOVE: {
			PlayerMoveEvent* playerMoveEvent = static_cast<PlayerMoveEvent*>(&newEvent);
			m_chunkManager->updateGenerationOrigin(playerMoveEvent->m_position);

			break;
		}
	}
}