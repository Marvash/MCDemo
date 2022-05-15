#include "MovementSystem.h"

MovementSystem::MovementSystem(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher), m_chunkManager(nullptr) {

}

void MovementSystem::init(ChunkManager* chunkManager) {
	m_chunkManager = chunkManager;
}

void MovementSystem::onNotify(Event& newEvent) {

}

void MovementSystem::step(double deltaTime) {
	for (auto& object : m_registeredObjects) {
		m_chunkManager->computeAdjacentCubes(object.second->adjacentCubes, object.first, object.second->movementComponent->m_adjacentCubesRadius);
	}
	for (auto& object : m_registeredObjects) {
		GameObject* gameObject = object.first;
		MovementComponent* movementComponent = object.second->movementComponent;
		switch (movementComponent->m_movementMode) {
			case MovementMode::DEFAULT: {
				stepPhysicalMovement(deltaTime, object.second);
				PlayerMoveEvent playerMoveEvent(gameObject->m_position);
				notify(playerMoveEvent);
				PlayerVelocityEvent playerVelocityEvent(movementComponent->m_velocity);
				notify(playerVelocityEvent);
				break;
			}
			case MovementMode::FLY:
				break;
			case MovementMode::FLYNOCLIP: {
				float frameSpeedMultiplier = movementComponent->m_flySpeed * deltaTime;
				gameObject->m_position += (movementComponent->m_velocity * frameSpeedMultiplier);
				PlayerMoveEvent playerMoveEvent(gameObject->m_position);
				notify(playerMoveEvent);
				movementComponent->m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
		}
	}
}

void MovementSystem::registerObject(GameObject* gameObject, MovementComponent* movementComponent) {
	PhysicsGameObject* physicsGO = new PhysicsGameObject();
	physicsGO->movementComponent = movementComponent;
	physicsGO->gameObject = gameObject;
	int size = (movementComponent->m_adjacentCubesRadius * 2) + 1;
	Cube*** adjacentCubes = new Cube * *[size];
	for (int i = 0; i < size; i++) {
		adjacentCubes[i] = new Cube * [size];
		for (int j = 0; j < size; j++) {
			adjacentCubes[i][j] = new Cube[size];
			for (int k = 0; k < size; k++) {
				adjacentCubes[i][j][k] = Cube();
			}
		}
	}
	physicsGO->adjacentCubes = adjacentCubes;
	m_registeredObjects.insert(std::make_pair(physicsGO->gameObject, physicsGO));
}

void MovementSystem::applyImpulse(MovementComponent* movementComponent, glm::vec3 vector) {
	movementComponent->m_velocity += vector;
}

void MovementSystem::stepPhysicalMovement(float dt, PhysicsGameObject* physicsGameObject) {
	int radius = physicsGameObject->movementComponent->m_adjacentCubesRadius;
	GameObject* go = physicsGameObject->gameObject;
	MovementComponent* mc = physicsGameObject->movementComponent;
	Cube*** adjacentCubes = physicsGameObject->adjacentCubes;
	AABBCollider* collider = &physicsGameObject->collider;
	if (physicsGameObject->adjacentCubes[radius][radius][radius].getCubeId() == Cube::CubeId::UNGENERATED_BLOCK) {
		return;
	}

	glm::vec3 centralCubeCoords = go->m_position;
	convertToCenteredCubeCoordinates(centralCubeCoords);

	float nearestBottomFaceDistance = glm::floor(go->m_position.y);
	float nearestTopFaceDistance = glm::ceil(go->m_position.y);

	go->m_position.y += mc->m_velocity.y * (float)dt;

	collider->position = go->m_position;
	collider->buildAABBCollider(go->m_position, mc->m_colliderHalfWidth, mc->m_colliderHalfHeight);
	float gravity = GRAVITY;

	// Bottom side
	glm::vec3 position = collider->bottomLeftFront;
	Cube::CubeId cubeId;
	bool vertical = true;
	bool horizontal = true;
	bool bottomCollision = false;
	while (vertical) {
		if (position.z < collider->bottomRightBack.z) {
			position.z = collider->bottomRightBack.z;
			vertical = false;
		}
		horizontal = true;
		position.x = collider->bottomLeftFront.x;
		while (horizontal) {
			if (position.x > collider->bottomRightFront.x) {
				position.x = collider->bottomRightFront.x;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			glm::vec3 lowerCubeCoords(position.x, position.y - 1.0f, position.z);
			Cube::CubeId lowerCubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, lowerCubeCoords, radius)->getCubeId();
			float delta = position.y - nearestBottomFaceDistance;
			if (((position.y < nearestBottomFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) || (delta >= 0.0f && delta < 0.001f) && lowerCubeId != Cube::CubeId::AIR_BLOCK) ) {
				go->m_position.y = nearestBottomFaceDistance + mc->m_colliderHalfHeight + 0.00001f;
				mc->m_velocity.y = 0.0f;
				mc->m_isGrounded = true;
				bottomCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.x += 1.0f;
		}
		position.z -= 1.0f;
	}
	//Top side
	position = collider->topLeftBack;
	vertical = true;
	horizontal = true;
	bool topCollision = false;
	while (vertical) {
		if (position.z > collider->topLeftFront.z) {
			position.z = collider->topLeftFront.z;
			vertical = false;
		}
		horizontal = true;
		position.x = collider->topLeftBack.x;
		while (horizontal) {
			if (position.x > collider->topRightBack.x) {
				position.x = collider->topRightBack.x;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			if (position.y > nearestTopFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) {
				go->m_position.y = nearestTopFaceDistance - mc->m_colliderHalfHeight - 0.00001f;
				mc->m_velocity.y = 0.0f;
				topCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.x += 1.0f;
		}
		position.z += 1.0f;
	}

	float nearestBackFaceDistance = glm::floor(go->m_position.z);
	float nearestFrontFaceDistance = glm::ceil(go->m_position.z);

	go->m_position.z += mc->m_velocity.z * mc->m_movementSpeed * (float)dt;
	collider->moveCollider(go->m_position);

	//Back side
	position = collider->topRightBack;
	vertical = true;
	horizontal = true;
	bool backCollision = false;
	while (vertical) {
		if (position.y < collider->bottomRightBack.y) {
			position.y = collider->bottomRightBack.y;
			vertical = false;
		}
		horizontal = true;
		position.x = collider->topRightBack.x;
		while (horizontal) {
			if (position.x < collider->topLeftBack.x) {
				position.x = collider->topLeftBack.x;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			if (position.z < nearestBackFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) {
				go->m_position.z = nearestBackFaceDistance + mc->m_colliderHalfWidth + 0.00001f;
				mc->m_velocity.z = 0.0f;
				backCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.x -= 1.0f;
		}
		position.y -= 1.0f;
	}

	//Front side
	position = collider->topLeftFront;
	vertical = true;
	horizontal = true;
	bool frontCollision = false;
	while (vertical) {
		if (position.y < collider->bottomLeftFront.y) {
			position.y = collider->bottomLeftFront.y;
			vertical = false;
		}
		horizontal = true;
		position.x = collider->topLeftFront.x;
		while (horizontal) {
			if (position.x > collider->topRightFront.x) {
				position.x = collider->topRightFront.x;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			if (position.z > nearestFrontFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) {
				go->m_position.z = nearestFrontFaceDistance - mc->m_colliderHalfWidth - 0.00001f;
				mc->m_velocity.z = 0.0f;
				frontCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.x += 1.0f;
		}
		position.y -= 1.0f;
	}

	float nearestLeftFaceDistance = glm::floor(go->m_position.x);
	float nearestRightFaceDistance = glm::ceil(go->m_position.x);
	go->m_position.x += mc->m_velocity.x * mc->m_movementSpeed * (float)dt;
	collider->moveCollider(go->m_position);

	//Left side
	position = collider->topLeftBack;
	vertical = true;
	horizontal = true;
	bool leftCollision = false;
	while (vertical) {
		if (position.y < collider->bottomLeftBack.y) {
			position.y = collider->bottomLeftBack.y;
			vertical = false;
		}
		horizontal = true;
		position.z = collider->topLeftBack.z;
		while (horizontal) {
			if (position.z > collider->topLeftFront.z) {
				position.z = collider->topLeftFront.z;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			if (position.x < nearestLeftFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) {
				go->m_position.x = nearestLeftFaceDistance + mc->m_colliderHalfWidth + 0.00001f;
				mc->m_velocity.x = 0.0f;
				leftCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.z += 1.0f;
		}
		position.y -= 1.0f;
	}

	//Right side
	position = collider->topRightFront;
	vertical = true;
	horizontal = true;
	bool rightCollision = false;
	while (vertical) {
		if (position.y < collider->bottomRightFront.y) {
			position.y = collider->bottomRightFront.y;
			vertical = false;
		}
		horizontal = true;
		position.z = collider->topRightFront.z;
		while (horizontal) {
			if (position.z < collider->topRightBack.z) {
				position.z = collider->topRightBack.z;
				horizontal = false;
			}
			cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
			if (position.x > nearestRightFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) {
				go->m_position.x = nearestRightFaceDistance - mc->m_colliderHalfWidth - 0.00001f;
				mc->m_velocity.x = 0.0f;
				rightCollision = true;
				horizontal = false;
				vertical = false;
			}
			position.z -= 1.0f;
		}
		position.y -= 1.0f;
	}

	if (!bottomCollision) {
		mc->m_velocity.y = glm::max(mc->m_velocity.y + (-gravity * mc->m_gravityInfluence * dt), -MAX_VELOCITY);
		mc->m_isGrounded = false;
	}
	mc->m_impulse = glm::vec3(0.0f);
}

Cube* MovementSystem::getAdjacentCubeByCoord(Cube*** adjacentCubes, glm::vec3& centralCubeCoords, glm::vec3& requestedCoords, int radius) {
	Cube* requestedCube = nullptr;
	int size = (radius * 2) + 1;
	glm::vec3 origin(centralCubeCoords.x - (float)radius - 0.5f, centralCubeCoords.y - (float)radius - 0.5f, centralCubeCoords.z - (float)radius - 0.5f);
	int h = int(requestedCoords.y - origin.y);
	int w = int(requestedCoords.x - origin.x);
	int d = int(requestedCoords.z - origin.z);
	if (h >= 0 && w >= 0 && d >= 0 && h < size && w < size && d < size) {
		requestedCube = &adjacentCubes[h][w][d];
	}
	return requestedCube;
}

void MovementSystem::convertToCenteredCubeCoordinates(glm::vec3& coords) {
	coords.x = glm::floor(coords.x) + 0.5f;
	coords.y = glm::floor(coords.y) + 0.5f;
	coords.z = glm::floor(coords.z) + 0.5f;
}