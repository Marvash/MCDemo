#include "MovementComponent.h"

MovementComponent::MovementComponent() :
	m_targetVelocity(glm::f64vec3(0.0, 0.0, 0.0)),
	m_velocity(glm::f64vec3(0.0, 0.0, 0.0)),
	m_previousPosition(glm::f64vec3(0.0, 0.0, 0.0)),
	m_currentPosition(glm::f64vec3(0.0, 0.0, 0.0)),
	m_previousVelocity(glm::f64vec3(0.0, 0.0, 0.0)),
	m_currentVelocity(glm::f64vec3(0.0, 0.0, 0.0)),
	m_movementSpeed(0.0f),
	m_flySpeed(0.0f),
	m_movementMode(MovementMode::STANDARD),
	m_isGrounded(false),
	m_gravityInfluence(1.0f),
	m_colliderHalfHeight(0.5f),
	m_colliderHalfWidth(0.5f),
	m_groundDampeningInfluence(1.0f),
	m_airDampeningInfluence(1.0f) {
}

glm::f64vec3 MovementComponent::getTargetVelocity() {
	return m_targetVelocity;
}
void MovementComponent::setTargetVelocity(glm::f64vec3 targetVelocity) {
	m_targetVelocity = targetVelocity;
}
glm::f64vec3 MovementComponent::getVelocity() {
	return m_velocity;
}
void MovementComponent::setVelocity(glm::f64vec3 velocity) {
	m_velocity = velocity;
}
float MovementComponent::getMovementSpeed() {
	return m_movementSpeed;
}
void MovementComponent::setMovementSpeed(float movementSpeed) {
	m_movementSpeed = movementSpeed;
}
float MovementComponent::getFlySpeed() {
	return m_flySpeed;
}
void MovementComponent::setFlySpeed(float flySpeed) {
	m_flySpeed = flySpeed;
}
bool MovementComponent::getIsGrounded() {
	return m_isGrounded;
}
float MovementComponent::getGravityInfluence() {
	return m_gravityInfluence;
}
void MovementComponent::setGravityInfluence(float influence) {
	m_gravityInfluence = influence;
}
float MovementComponent::getGroundDampeningInfluence() {
	return m_groundDampeningInfluence;
}
void MovementComponent::setGroundDampeningInfluence(float influence) {
	m_groundDampeningInfluence = influence;
}
float MovementComponent::getAirDampeningInfluence() {
	return m_airDampeningInfluence;
}
void MovementComponent::setAirDampeningInfluence(float influence) {
	m_airDampeningInfluence = influence;
}
float MovementComponent::getColliderHalfHeight() {
	return m_colliderHalfHeight;
}
void MovementComponent::setColliderHalfHeight(float halfHeight) {
	m_colliderHalfHeight = halfHeight;
}
float MovementComponent::getColliderHalfWidth() {
	return m_colliderHalfWidth;
}
void MovementComponent::setColliderHalfWidth(float halfWidth) {
	m_colliderHalfWidth = halfWidth;
}
MovementMode MovementComponent::getMovementMode() {
	return m_movementMode;
}