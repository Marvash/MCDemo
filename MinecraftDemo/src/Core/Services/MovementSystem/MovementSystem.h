#pragma once
#include "Core/CoreEventDispatcher.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Components/MovementComponent.h"
#include "Core/Events/Game/PlayerMoveEvent.h"
#include "AABBCollider.h"

class MovementComponent;

class MovementSystem : public CoreService {
public:
	struct PhysicsGameObject {
		GameObject* gameObject;
		MovementComponent* movementComponent;
		Cube*** adjacentCubes;
		AABBCollider collider;
	};

	MovementSystem(CoreEventDispatcher* coreEventDispatcher);
	void init( ChunkManager* chunkManager);
	void onNotify(Event& newEvent) override;
	void registerObject(GameObject* gameObject, MovementComponent* movementComponent);
	void step(double deltaTime);
	void applyImpulse(MovementComponent* movementComponent, glm::vec3 vector);

	std::map<GameObject*, PhysicsGameObject*> m_registeredObjects;

private:
	void stepPhysicalMovement(float dt, PhysicsGameObject* physicsGameObject);
	Cube* getAdjacentCubeByCoord(Cube*** adjacentCubes, glm::vec3& centralCubeCoords, glm::vec3& requestedCoords, int radius);
	void convertToCenteredCubeCoordinates(glm::vec3& coords);

	const float GRAVITY = 30.0f;
	const float MAX_VELOCITY = 50.0f;
	ChunkManager* m_chunkManager;
};