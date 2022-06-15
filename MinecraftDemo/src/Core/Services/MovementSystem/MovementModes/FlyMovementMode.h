#pragma once
#include "Utils/Strategy/Strategy.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Services/MovementSystem/AABBCollider.h"
#include "Core/Services/ChunkManager/ChunkManager.h"

class FlyMovementMode : public Strategy
{
public:
	FlyMovementMode();
	void updateAccumulator(double deltaTime);

	GameObject* m_go;
	MovementComponent* m_mc;
	ChunkManager* m_chunkManager;
	double m_deltaTime;

private:
	void execute() override;
	void stepPhysicalMovement();
	void computeInterpolatedPosition(float alpha, GameObject* gameObject, MovementComponent* movementComponent);

	const float AIR_VELOCITY_LERP_FACTOR = 0.2f;
	const float MAX_VELOCITY = 150.0f;
	const float FIXED_DELTA = 0.05f;
	const float COLLISION_OFFSET = 0.00001f;

	double m_accumulator;
	int m_nSteps;
	float m_alpha;

	friend class StrategyContext;
};
