#pragma once
#include "Utils/Strategy/Strategy.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Services/MovementSystem/AABBCollider.h"
#include "Core/Services/ChunkManager/ChunkManager.h"

class StandardMovementMode : public Strategy
{
public:
	StandardMovementMode();
	void updateAccumulator(double deltaTime);

	GameObject* m_go;
	MovementComponent* m_mc;
	ChunkManager* m_chunkManager;
	double m_deltaTime;

private:
	void execute() override;
	void stepPhysicalMovement();
	void computeInterpolatedPosition(double alpha, GameObject* gameObject, MovementComponent* movementComponent);

	const double GRAVITY = 30.0;
	const double GROUND_VELOCITY_LERP_FACTOR = 0.45;
	const double AIR_VELOCITY_LERP_FACTOR = 0.1;
	const double MAX_VELOCITY = 150.0;
	const double FIXED_DELTA = 0.05;
	const double COLLISION_OFFSET = 0.00001;

	double m_accumulator;
	int m_nSteps;
	double m_alpha;

	friend class StrategyContext;
};

