#include "World.h"

World::World(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_threadsRunning(false),
	m_cameraSystem(nullptr) {

}

void World::init(ChunkManager* chunkManager, CameraSystem* cameraSystem) {
	m_chunkManager = chunkManager;
	m_cameraSystem = cameraSystem;
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

Block* World::getFirstNonEmptyBlock(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength) {
	Block* target = nullptr;
	std::vector<Block*> cubesInRay;
	//BOOST_LOG_TRIVIAL(info) << "player pos: " << m_position.x << " " << m_position.y << " " << m_position.z;
	//BOOST_LOG_TRIVIAL(info) << "player campos: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z;
	//BOOST_LOG_TRIVIAL(info) << "player front: " << cameraLookDir.x << " " << cameraLookDir.y << " " << cameraLookDir.z;
	getCubesInRay(rayOrigin, rayDirection, rayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			glm::vec3 cubeCoords = getCubeAbsCoords(cubesInRay.at(i));
			//BOOST_LOG_TRIVIAL(info) << "cube " << i << " coords: " << cubeCoords.x << " " << cubeCoords.y << " " << cubeCoords.z;
			if (cubesInRay.at(i)->getBlockId() != BlockId::AIR && cubesInRay.at(i)->getBlockId() != BlockId::NONE) {
				target = cubesInRay.at(i);
				//BOOST_LOG_TRIVIAL(info) << "target is cube " << i;
				break;
			}
		}
	}
	return target;
}

Block* World::getLastEmptyBlock(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength) {
	Block* target = nullptr;
	std::vector<Block*> cubesInRay;
	glm::vec3 cameraPos = m_cameraSystem->getCameraPosition();
	glm::vec3 cameraLookDir = m_cameraSystem->m_front;
	getCubesInRay(cameraPos, cameraLookDir, rayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			if (i > 0 && cubesInRay.at(i)->getBlockId() != BlockId::AIR && cubesInRay.at(i)->getBlockId() != BlockId::NONE) {
				target = cubesInRay.at(i - 1);
				break;
			}
		}
	}
	return target;
}

void World::onNotify(Event& newEvent) {
}
