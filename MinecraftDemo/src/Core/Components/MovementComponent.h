#pragma once
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include <glm/glm.hpp>

class MovementComponent {



public:
	MovementComponent();
	glm::vec3 getTargetVelocity();
	void setTargetVelocity(glm::vec3 targetVelocity);
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 velocity);
	float getMovementSpeed();
	void setMovementSpeed(float movementSpeed);
	float getFlySpeed();                                               
	void setFlySpeed(float flySpeed);
	bool getIsGrounded();
	float getGravityInfluence();
	void setGravityInfluence(float influence);
	float getGroundDampeningInfluence();
	void setGroundDampeningInfluence(float influence);
	float getAirDampeningInfluence();
	void setAirDampeningInfluence(float influence);
	float getColliderHalfHeight();
	void setColliderHalfHeight(float halfHeight);
	float getColliderHalfWidth();
	void setColliderHalfWidth(float halfWidth);
	MovementMode getMovementMode();

private:
	glm::vec3 m_targetVelocity;
	glm::vec3 m_velocity;
	glm::vec3 m_previousPosition;
	glm::vec3 m_currentPosition;
	glm::vec3 m_previousVelocity;
	glm::vec3 m_currentVelocity;
	float m_movementSpeed;
	float m_flySpeed;
	MovementMode m_movementMode;
	bool m_isGrounded;
	float m_gravityInfluence;
	float m_groundDampeningInfluence;
	float m_airDampeningInfluence;

	float m_colliderHalfHeight;
	float m_colliderHalfWidth;

	friend class StandardMovementMode;
	friend class FlyNoClipMovementMode;
	friend class FlyMovementMode;
	friend class MovementSystem;
};