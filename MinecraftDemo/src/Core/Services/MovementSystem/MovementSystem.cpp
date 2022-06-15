#include "MovementSystem.h"

MovementSystem::MovementSystem(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher), 
	m_chunkManager(nullptr),
	m_movementStrategyContext(new StrategyContext()),
	m_standardMovementMode(new StandardMovementMode()),
	m_flyNoClipMovementMode(new FlyNoClipMovementMode()),
	m_flyMovementMode(new FlyMovementMode()) {
}

MovementSystem::~MovementSystem() {
	delete m_movementStrategyContext;
	delete m_standardMovementMode;
	delete m_flyNoClipMovementMode;
	delete m_flyMovementMode;
}

void MovementSystem::init(ChunkManager* chunkManager) {
	m_chunkManager = chunkManager;
	m_standardMovementMode->m_chunkManager = m_chunkManager;
	m_flyMovementMode->m_chunkManager = m_chunkManager;
}

void MovementSystem::onNotify(Event& newEvent) {

}

void MovementSystem::update(double deltaTime) {
	m_standardMovementMode->updateAccumulator(deltaTime);
	m_flyMovementMode->updateAccumulator(deltaTime);
	m_flyNoClipMovementMode->m_deltaTime = deltaTime;
	for (auto& object : m_registeredObjects) {
		GameObject* gameObject = object.first;
		MovementComponent* movementComponent = object.second;
		switch (movementComponent->m_movementMode) {
		case MovementMode::STANDARD: {
			m_standardMovementMode->m_go = gameObject;
			m_standardMovementMode->m_mc = movementComponent;
			m_movementStrategyContext->setStrategy(m_standardMovementMode);
			m_movementStrategyContext->execute();
			break;
		}
		case MovementMode::FLY:
			m_flyMovementMode->m_go = gameObject;
			m_flyMovementMode->m_mc = movementComponent;
			m_movementStrategyContext->setStrategy(m_flyMovementMode);
			m_movementStrategyContext->execute();
			break;
		case MovementMode::FLYNOCLIP: {
			m_flyNoClipMovementMode->m_go = gameObject;
			m_flyNoClipMovementMode->m_mc = movementComponent;
			m_movementStrategyContext->setStrategy(m_flyNoClipMovementMode);
			m_movementStrategyContext->execute();
			break;
		}
		}
	}
}

void MovementSystem::registerObject(GameObject* gameObject, MovementComponent* movementComponent) {
	if (m_registeredObjects.find(gameObject) == m_registeredObjects.end()) {
		m_registeredObjects.insert(std::make_pair(gameObject, movementComponent));
	}
}

void MovementSystem::setMovementMode(GameObject* gameObject, MovementMode movementMode) {
	if (m_registeredObjects.find(gameObject) == m_registeredObjects.end()) {
		return;
	}
	MovementComponent* mc = m_registeredObjects.at(gameObject);
	if (movementMode == MovementMode::STANDARD || movementMode == MovementMode::FLY) {
		mc->m_currentPosition = gameObject->m_position;
		mc->m_previousPosition = mc->m_currentPosition;
	}
	mc->m_movementMode = movementMode;
}

std::string MovementSystem::getMovementModeDisplayName(MovementMode movementMode) {
	switch (movementMode) {
	case MovementMode::STANDARD:
		return std::string("Standard");
	case MovementMode::FLY:
		return std::string("Fly");
	case MovementMode::FLYNOCLIP:
		return std::string("Fly No Clip");
	}
	return std::string("Unknown Movement Mode");
}