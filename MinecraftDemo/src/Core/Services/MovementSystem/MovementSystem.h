#pragma once
#include "Core/CoreEventDispatcher.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Components/MovementComponent.h"
#include "Utils/Strategy/StrategyContext.h"
#include "Utils/Strategy/Strategy.h"
#include "Core/Services/MovementSystem/MovementModes/StandardMovementMode.h"
#include "Core/Services/MovementSystem/MovementModes/FlyNoClipMovementMode.h"
#include "Core/Services/MovementSystem/MovementModes/FlyMovementMode.h"
#include "AABBCollider.h"

class MovementComponent;

class MovementSystem : public CoreService {
public:
	MovementSystem(CoreEventDispatcher* coreEventDispatcher);
	~MovementSystem();
	void init(ChunkManager* chunkManager);
	void onNotify(Event& newEvent) override;
	void registerObject(GameObject* gameObject, MovementComponent* movementComponent);
	void update(double deltaTime);
	void setMovementMode(GameObject* gameObject, MovementMode movementMode);
	std::string getMovementModeDisplayName(MovementMode movementMode);

	std::map<GameObject*, MovementComponent*> m_registeredObjects;

private:
	ChunkManager* m_chunkManager;
	StrategyContext* m_movementStrategyContext;
	StandardMovementMode* m_standardMovementMode;
	FlyNoClipMovementMode* m_flyNoClipMovementMode;
	FlyMovementMode* m_flyMovementMode;
};