#pragma once
#include "Utils/Strategy/Strategy.h"
#include "Core/GameObject/GameObject.h"

class FlyNoClipMovementMode : public Strategy
{
public:
	FlyNoClipMovementMode();

	GameObject* m_go;
	MovementComponent* m_mc;
	double m_deltaTime;

private:
	void execute() override;

	friend class StrategyContext;
};
