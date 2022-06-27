#include "StandardMovementMode.h"

StandardMovementMode::StandardMovementMode() :
	Strategy(),
	m_go(nullptr),
	m_mc(nullptr),
	m_chunkManager(nullptr),
	m_accumulator(0.0),
	m_deltaTime(0.0),
	m_nSteps(0),
	m_alpha(0.0f) {

}

void StandardMovementMode::updateAccumulator(double deltaTime) {
	m_accumulator += deltaTime;
	m_nSteps = m_accumulator / FIXED_DELTA;
	m_accumulator -= m_nSteps * FIXED_DELTA;
	m_alpha = m_accumulator / FIXED_DELTA;
}

void StandardMovementMode::execute() {
	for (int i = 0; i < m_nSteps; i++) {
		stepPhysicalMovement();
	}
	computeInterpolatedPosition(m_alpha, m_go, m_mc);
}

void StandardMovementMode::stepPhysicalMovement() {
	GameObject* go = m_go;
	MovementComponent* mc = m_mc;
	AABBCollider collider;
	if (m_chunkManager->getCubeByCoords(go->m_position) == nullptr || m_chunkManager->getCubeByCoords(go->m_position)->getCubeId() == Cube::CubeId::UNGENERATED_BLOCK) {
		return;
	}

	mc->m_previousPosition = mc->m_currentPosition;
	mc->m_previousVelocity = mc->m_currentVelocity;

	glm::f64vec3 targetVelNorm(0.0, 0.0, 0.0);
	if (glm::length(mc->m_targetVelocity) > 0.0) {
		targetVelNorm = glm::normalize(mc->m_targetVelocity);
	}

	double gravity = GRAVITY * mc->m_gravityInfluence;
	mc->m_velocity.y = mc->m_velocity.y + (-gravity * mc->m_gravityInfluence * FIXED_DELTA);
	double lerpFactor = mc->m_isGrounded ? GROUND_VELOCITY_LERP_FACTOR * mc->m_groundDampeningInfluence : AIR_VELOCITY_LERP_FACTOR * mc->m_airDampeningInfluence;
	//mc->m_velocity.z = cubicInterpolation();
	mc->m_velocity.z = mc->m_velocity.z + ((mc->m_targetVelocity.z - mc->m_velocity.z) * lerpFactor);
	mc->m_velocity.x = mc->m_velocity.x + ((mc->m_targetVelocity.x - mc->m_velocity.x) * lerpFactor);

	if (glm::length(mc->m_velocity) > MAX_VELOCITY) {
		mc->m_velocity = glm::normalize(mc->m_velocity) * MAX_VELOCITY;
	}
	/*
	float velocityFactorZ = mc->m_isGrounded ? GROUND_VELOCITY_LERP_FACTOR : AIR_VELOCITY_LERP_FACTOR;
	if (mc->m_targetVelocity.z > 0.0f) {
		velocityFactorZ *= targetVelNorm.z;
	}
	float velocityDecrementZ = glm::sign(mc->m_targetVelocity.z - mc->m_velocity.z) * velocityFactorZ * FIXED_DELTA;
	if (glm::abs(velocityDecrementZ) > glm::abs(mc->m_targetVelocity.z - mc->m_velocity.z)) {
		velocityDecrementZ = mc->m_targetVelocity.z - mc->m_velocity.z;
	}
	mc->m_velocity.z = mc->m_velocity.z + velocityDecrementZ;
	float velocityFactorX = mc->m_isGrounded ? GROUND_VELOCITY_LERP_FACTOR : AIR_VELOCITY_LERP_FACTOR;
	if (mc->m_targetVelocity.x > 0.0f) {
		velocityFactorZ *= targetVelNorm.x;
	}
	float velocityDecrementX = glm::sign(mc->m_targetVelocity.x - mc->m_velocity.x) * velocityFactorX * FIXED_DELTA;
	if (glm::abs(velocityDecrementX) > glm::abs(mc->m_targetVelocity.x - mc->m_velocity.x)) {
		velocityDecrementX = mc->m_targetVelocity.x - mc->m_velocity.x;
	}
	mc->m_velocity.x = mc->m_velocity.x + velocityDecrementX;
	*/
	glm::f64vec3 targetPosition = mc->m_currentPosition;
	collider.buildAABBCollider(mc->m_currentPosition, mc->m_colliderHalfWidth, mc->m_colliderHalfHeight);

	targetPosition.y += mc->m_velocity.y * FIXED_DELTA;
	//BOOST_LOG_TRIVIAL(info) << "gy: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;

	//BOOST_LOG_TRIVIAL(info) << "aabb: " << collider.bottomRightBack.x << " " << collider.bottomRightBack.y << " " << collider.bottomRightBack.z;

	glm::f64vec3 targetDistance = targetPosition;

	glm::f64vec3 colliderVertexPosition = collider.bottomLeftFront;
	bool vertical = true;
	bool horizontal = true;
	bool depth = true;
	bool bottomCollision = false;
	bool topCollision = false;
	bool backCollision = false;
	bool frontCollision = false;
	bool leftCollision = false;
	bool rightCollision = false;
	Cube::CubeId cubeId;
	double nearestCubes = 0.0;
	// Bottom side
	if (mc->m_velocity.y < 0.0) {
		targetDistance.y -= mc->m_colliderHalfHeight;
		//BOOST_LOG_TRIVIAL(info) << "POS2: " << targetPosition.y;
		//BOOST_LOG_TRIVIAL(info) << "DISTANCE: " << glm::abs(targetDistance.y - colliderVertexPosition.y) << " " << mc->m_velocity.y << " " << targetDistance.y;
		do {
			nearestCubes = glm::floor(colliderVertexPosition.y);
			if (glm::abs(targetDistance.y - colliderVertexPosition.y) < 1.0) {
				colliderVertexPosition.y = targetDistance.y;
				depth = false;
			}
			else {
				colliderVertexPosition.y += (glm::sign(mc->m_velocity.y) * 1.0);
			}
			//BOOST_LOG_TRIVIAL(info) << "sub: " << colliderVertexPosition.y;
			if (colliderVertexPosition.y < nearestCubes) {
				colliderVertexPosition.z = collider.bottomLeftFront.z;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.z < collider.bottomRightBack.z) {
						colliderVertexPosition.z = collider.bottomRightBack.z;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.x = collider.bottomLeftFront.x;
					while (horizontal) {
						if (colliderVertexPosition.x > collider.bottomRightFront.x) {
							colliderVertexPosition.x = collider.bottomRightFront.x;
							horizontal = false;
						}
						Cube* cube = m_chunkManager->getCubeByCoords(colliderVertexPosition);
						//BOOST_LOG_TRIVIAL(info) << "CUBE1: " << m_chunkManager->getCubeAbsCoords(cube).y;
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.y = glm::ceil(colliderVertexPosition.y) + mc->m_colliderHalfHeight + COLLISION_OFFSET;
							//BOOST_LOG_TRIVIAL(info) << "Final pos: " << targetPosition.y;
							bottomCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						/*
						cubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, position, radius)->getCubeId();
						glm::vec3 lowerCubeCoords(position.x, position.y - 1.0f, position.z);
						Cube::CubeId lowerCubeId = getAdjacentCubeByCoord(adjacentCubes, centralCubeCoords, lowerCubeCoords, radius)->getCubeId();
						float delta = position.y - nearestBottomFaceDistance;
						if (((position.y < nearestBottomFaceDistance && cubeId != Cube::CubeId::AIR_BLOCK) || (delta >= 0.0f && delta < 0.001f) && lowerCubeId != Cube::CubeId::AIR_BLOCK)) {
							mc->m_currentPosition.y = nearestBottomFaceDistance + mc->m_colliderHalfHeight + 0.00001f;
							mc->m_velocity.y = 0.0f;
							mc->m_isGrounded = true;
							bottomCollision = true;
							horizontal = false;
							vertical = false;
						}
						*/
						colliderVertexPosition.x += 1.0;
					}
					colliderVertexPosition.z -= 1.0;
				}
			}
		} while (depth);
	}
	//Top side
	if (mc->m_velocity.y > 0.0) {
		targetDistance.y += mc->m_colliderHalfHeight;
		colliderVertexPosition = collider.topLeftBack;
		vertical = true;
		horizontal = true;
		depth = true;
		do {
			nearestCubes = glm::ceil(colliderVertexPosition.y);
			if (glm::abs(targetDistance.y - colliderVertexPosition.y) < 1.0) {
				colliderVertexPosition.y = targetDistance.y;
				depth = false;
			}
			else {
				colliderVertexPosition.y += (glm::sign(mc->m_velocity.y) * 1.0);
			}
			if (colliderVertexPosition.y > nearestCubes) {
				colliderVertexPosition.z = collider.topLeftBack.z;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.z > collider.topLeftFront.z) {
						colliderVertexPosition.z = collider.topLeftFront.z;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.x = collider.topLeftBack.x;
					while (horizontal) {
						if (colliderVertexPosition.x > collider.topRightBack.x) {
							colliderVertexPosition.x = collider.topRightBack.x;
							horizontal = false;
						}
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.y = glm::floor(colliderVertexPosition.y) - mc->m_colliderHalfHeight - COLLISION_OFFSET;
							topCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						colliderVertexPosition.x += 1.0;
					}
					colliderVertexPosition.z += 1.0;
				}
			}
		} while (depth);
	}

	//BOOST_LOG_TRIVIAL(info) << "gyc: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;
	collider.moveCollider(targetPosition);

	targetPosition.z += mc->m_velocity.z * FIXED_DELTA;
	//BOOST_LOG_TRIVIAL(info) << "gz: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;
	targetDistance = targetPosition;
	//Back side
	if (mc->m_velocity.z < 0.0) {
		targetDistance.z -= mc->m_colliderHalfWidth;
		colliderVertexPosition = collider.topRightBack;
		vertical = true;
		horizontal = true;
		depth = true;
		do {
			nearestCubes = glm::floor(colliderVertexPosition.z);
			if (glm::abs(targetDistance.z - colliderVertexPosition.z) < 1.0) {
				colliderVertexPosition.z = targetDistance.z;
				depth = false;
			}
			else {
				colliderVertexPosition.z += (glm::sign(mc->m_velocity.z) * 1.0);
			}
			if (colliderVertexPosition.z < nearestCubes) {
				colliderVertexPosition.y = collider.topRightBack.y;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.y < collider.bottomRightBack.y) {
						colliderVertexPosition.y = collider.bottomRightBack.y;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.x = collider.topRightBack.x;
					while (horizontal) {
						if (colliderVertexPosition.x < collider.topLeftBack.x) {
							colliderVertexPosition.x = collider.topLeftBack.x;
							horizontal = false;
						}
						Cube* cube = m_chunkManager->getCubeByCoords(colliderVertexPosition);
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.z = glm::ceil(colliderVertexPosition.z) + mc->m_colliderHalfWidth + COLLISION_OFFSET;
							backCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						colliderVertexPosition.x -= 1.0;
					}
					colliderVertexPosition.y -= 1.0;
				}
			}
		} while (depth);
	}
	//Front side
	if (mc->m_velocity.z > 0.0) {
		targetDistance.z += mc->m_colliderHalfWidth;
		colliderVertexPosition = collider.topLeftFront;
		vertical = true;
		horizontal = true;
		depth = true;
		do {
			nearestCubes = glm::ceil(colliderVertexPosition.z);
			if (glm::abs(targetDistance.z - colliderVertexPosition.z) < 1.0) {
				colliderVertexPosition.z = targetDistance.z;
				depth = false;
			}
			else {
				colliderVertexPosition.z += (glm::sign(mc->m_velocity.z) * 1.0);
			}
			if (colliderVertexPosition.z > nearestCubes) {
				colliderVertexPosition.y = collider.topLeftFront.y;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.y < collider.bottomLeftFront.y) {
						colliderVertexPosition.y = collider.bottomLeftFront.y;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.x = collider.topLeftFront.x;
					while (horizontal) {
						if (colliderVertexPosition.x > collider.topRightFront.x) {
							colliderVertexPosition.x = collider.topRightFront.x;
							horizontal = false;
						}
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.z = glm::floor(colliderVertexPosition.z) - mc->m_colliderHalfWidth - COLLISION_OFFSET;
							frontCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						colliderVertexPosition.x += 1.0;
					}
					colliderVertexPosition.y -= 1.0;
				}
			}
		} while (depth);
	}
	//BOOST_LOG_TRIVIAL(info) << "gzc: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;
	collider.moveCollider(targetPosition);

	targetPosition.x += mc->m_velocity.x * FIXED_DELTA;
	//BOOST_LOG_TRIVIAL(info) << "gx: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;
	targetDistance = targetPosition;
	//Left side
	if (mc->m_velocity.x < 0.0) {
		targetDistance.x -= mc->m_colliderHalfWidth;
		colliderVertexPosition = collider.topLeftBack;
		vertical = true;
		horizontal = true;
		depth = true;
		do {
			nearestCubes = glm::floor(colliderVertexPosition.x);
			if (glm::abs(targetDistance.x - colliderVertexPosition.x) < 1.0) {
				colliderVertexPosition.x = targetDistance.x;
				depth = false;
			}
			else {
				colliderVertexPosition.x += (glm::sign(mc->m_velocity.x) * 1.0);
			}
			if (colliderVertexPosition.x < nearestCubes) {
				colliderVertexPosition.y = collider.topLeftBack.y;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.y < collider.bottomLeftBack.y) {
						colliderVertexPosition.y = collider.bottomLeftBack.y;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.z = collider.topLeftBack.z;
					while (horizontal) {
						if (colliderVertexPosition.z > collider.topLeftFront.z) {
							colliderVertexPosition.z = collider.topLeftFront.z;
							horizontal = false;
						}
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.x = glm::ceil(colliderVertexPosition.x) + mc->m_colliderHalfWidth + COLLISION_OFFSET;
							leftCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						colliderVertexPosition.z += 1.0;
					}
					colliderVertexPosition.y -= 1.0;
				}
			}
		} while (depth);
	}
	//Right side
	if (mc->m_velocity.x > 0.0) {
		targetDistance.x += mc->m_colliderHalfWidth;
		colliderVertexPosition = collider.topRightFront;
		vertical = true;
		horizontal = true;
		depth = true;
		do {
			nearestCubes = glm::ceil(colliderVertexPosition.x);
			if (glm::abs(targetDistance.x - colliderVertexPosition.x) < 1.0) {
				colliderVertexPosition.x = targetDistance.x;
				depth = false;
			}
			else {
				colliderVertexPosition.x += (glm::sign(mc->m_velocity.x) * 1.0);
			}
			if (colliderVertexPosition.x > nearestCubes) {
				colliderVertexPosition.y = collider.topRightFront.y;
				vertical = true;
				while (vertical) {
					if (colliderVertexPosition.y < collider.bottomRightFront.y) {
						colliderVertexPosition.y = collider.bottomRightFront.y;
						vertical = false;
					}
					horizontal = true;
					colliderVertexPosition.z = collider.topRightFront.z;
					while (horizontal) {
						if (colliderVertexPosition.z < collider.topRightBack.z) {
							colliderVertexPosition.z = collider.topRightBack.z;
							horizontal = false;
						}
						cubeId = m_chunkManager->getCubeByCoords(colliderVertexPosition)->getCubeId();
						if (cubeId != Cube::CubeId::AIR_BLOCK) {
							targetPosition.x = glm::floor(colliderVertexPosition.x) - mc->m_colliderHalfWidth - COLLISION_OFFSET;
							//BOOST_LOG_TRIVIAL(info) << "r: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;
							rightCollision = true;
							horizontal = false;
							vertical = false;
							depth = false;
						}
						colliderVertexPosition.z -= 1.0;
					}
					colliderVertexPosition.y -= 1.0;
				}
			}
		} while (depth);
	}
	//BOOST_LOG_TRIVIAL(info) << "gxc: " << go->m_position.x << " " << go->m_position.y << " " << go->m_position.z;


	if (bottomCollision) {
		mc->m_velocity.y = 0.0;
		mc->m_isGrounded = true;
	}
	else {
		mc->m_isGrounded = false;
	}
	if (topCollision) {
		mc->m_velocity.y = 0.0;
	}
	if (leftCollision) {
		mc->m_velocity.x = 0.0;
	}
	if (rightCollision) {
		mc->m_velocity.x = 0.0;
	}
	if (frontCollision) {
		mc->m_velocity.z = 0.0;
	}
	if (backCollision) {
		mc->m_velocity.z = 0.0;
	}

	mc->m_currentPosition = targetPosition;
	mc->m_currentVelocity = mc->m_velocity;
}

void StandardMovementMode::computeInterpolatedPosition(double alpha, GameObject* gameObject, MovementComponent* movementComponent) {
	GameObject* go = gameObject;
	MovementComponent* mc = movementComponent;
	go->m_position = (mc->m_currentPosition * alpha) + (mc->m_previousPosition * (1.0 - alpha));
}