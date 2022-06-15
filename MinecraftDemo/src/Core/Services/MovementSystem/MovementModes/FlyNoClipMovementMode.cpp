#include "FlyNoClipMovementMode.h"

FlyNoClipMovementMode::FlyNoClipMovementMode() : 
	Strategy(),
	m_go(nullptr),
	m_mc(nullptr),
	m_deltaTime(0.0) {

}

void FlyNoClipMovementMode::execute() {
	GameObject* go = m_go;
	MovementComponent* mc = m_mc;
	mc->m_velocity = mc->m_targetVelocity;
	go->m_position += (mc->m_velocity * (float)m_deltaTime);
}