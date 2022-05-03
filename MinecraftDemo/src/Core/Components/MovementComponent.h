#pragma once
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include <glm/glm.hpp>

class MovementComponent {

public:
	MovementComponent() :
	m_velocity(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_movementSpeed(0.0f),
	m_fallingMovementSpeed(0.0f),
	m_flySpeed(0.0f),
	m_movementMode(MovementMode::DEFAULT),
	m_adjacentCubesRadius(3),
	m_isGrounded(false),
	m_gravityInfluence(1.0f),
	m_colliderHalfHeight(0.9f),
	m_colliderHalfWidth(0.3f),
	m_jumpStrength(0.0f) {}

	glm::vec3 m_velocity;
	glm::vec3 m_impulse;
	float m_movementSpeed;
	float m_fallingMovementSpeed;
	float m_flySpeed;
	MovementMode m_movementMode;
	bool m_isGrounded;
	float m_gravityInfluence;
	float m_jumpStrength;

private:
	int m_adjacentCubesRadius;
	float m_colliderHalfHeight;
	float m_colliderHalfWidth;

	friend class MovementSystem;
};