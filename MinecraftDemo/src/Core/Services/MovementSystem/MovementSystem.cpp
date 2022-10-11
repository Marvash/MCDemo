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

bool MovementSystem::AABBCollision(const AABBCollider* collider1, const AABBCollider* collider2) {
	const AABBCollider* smallerCollider = collider1;
	const AABBCollider* biggerCollider = collider2;
	if ((collider1->bottomRightBack.x - collider1->bottomLeftBack.x) <= (collider2->bottomRightBack.x - collider2->bottomLeftBack.x)) {
		smallerCollider = collider1;
		biggerCollider = collider2;
	}
	else {
		smallerCollider = collider2;
		biggerCollider = collider1;
	}
	if (((smallerCollider->bottomLeftBack.x >= biggerCollider->bottomLeftBack.x) && (smallerCollider->bottomLeftBack.x <= biggerCollider->bottomRightBack.x)) || ((smallerCollider->bottomRightBack.x >= biggerCollider->bottomLeftBack.x) && (smallerCollider->bottomRightBack.x <= biggerCollider->bottomRightBack.x))) {
		if ((collider1->bottomLeftFront.z - collider1->bottomLeftBack.z) <= (collider2->bottomLeftFront.z - collider2->bottomLeftBack.z)) {
			smallerCollider = collider1;
			biggerCollider = collider2;
		}
		else {
			smallerCollider = collider2;
			biggerCollider = collider1;
		}
		if (((smallerCollider->bottomLeftBack.z >= biggerCollider->bottomLeftBack.z) && (smallerCollider->bottomLeftBack.z <= biggerCollider->bottomLeftFront.z)) || ((smallerCollider->bottomLeftFront.z >= biggerCollider->bottomLeftBack.z) && (smallerCollider->bottomLeftFront.z <= biggerCollider->bottomLeftFront.z))) {
			if ((collider1->topLeftBack.y - collider1->bottomLeftBack.y) <= (collider2->topLeftBack.y - collider2->bottomLeftBack.y)) {
				smallerCollider = collider1;
				biggerCollider = collider2;
			}
			else {
				smallerCollider = collider2;
				biggerCollider = collider1;
			}
			if (((smallerCollider->bottomLeftBack.y >= biggerCollider->bottomLeftBack.y) && (smallerCollider->bottomLeftBack.y <= biggerCollider->topLeftBack.y)) || ((smallerCollider->topLeftBack.y >= biggerCollider->bottomLeftBack.y) && (smallerCollider->topLeftBack.y <= biggerCollider->topLeftBack.y))) {
				return true;
			}
		}
	}
	return false;
}

bool MovementSystem::isObjectInBlock(GameObject* gameObject, Block* block) {
	for (auto& object : m_registeredObjects) {
		if (gameObject == object.first) {
			GameObject* gameObject = object.first;
			MovementComponent* mc = object.second;
			AABBCollider collider;
			collider.buildAABBCollider(mc->m_currentPosition, mc->m_colliderHalfWidth, mc->m_colliderHalfHeight);
			glm::f64vec3 blockCoords = m_chunkManager->getCubeAbsCoords(block);
			AABBCollider blockCollider;
			blockCollider.buildAABBCollider(blockCoords, Chunk::blockSideSize / 2.0f, Chunk::blockSideSize / 2.0f);
			return AABBCollision(&collider, &blockCollider);
		}
	}
	return false;
}