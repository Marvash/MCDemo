#pragma once
#include <glm/glm.hpp>

struct AABBCollider {
	float halfWidthInternal;
	float halfHeightInternal;

	glm::vec3 position;

	glm::vec3 bottomLeftFront;
	glm::vec3 bottomRightFront;
	glm::vec3 bottomRightBack;
	glm::vec3 bottomLeftBack;
	glm::vec3 topLeftBack;
	glm::vec3 topRightBack;
	glm::vec3 topRightFront;
	glm::vec3 topLeftFront;

	void buildAABBCollider(glm::vec3& position, float halfWidth, float halfHeight) {
		bottomLeftFront.x = position.x - halfWidth;
		bottomLeftFront.y = position.y - halfHeight;
		bottomLeftFront.z = position.z + halfWidth;

		bottomRightFront.x = position.x + halfWidth;
		bottomRightFront.y = position.y - halfHeight;
		bottomRightFront.z = position.z + halfWidth;

		bottomRightBack.x = position.x + halfWidth;
		bottomRightBack.y = position.y - halfHeight;
		bottomRightBack.z = position.z - halfWidth;

		bottomLeftBack.x = position.x - halfWidth;
		bottomLeftBack.y = position.y - halfHeight;
		bottomLeftBack.z = position.z - halfWidth;

		topLeftFront.x = position.x - halfWidth;
		topLeftFront.y = position.y + halfHeight;
		topLeftFront.z = position.z + halfWidth;

		topRightFront.x = position.x + halfWidth;
		topRightFront.y = position.y + halfHeight;
		topRightFront.z = position.z + halfWidth;

		topRightBack.x = position.x + halfWidth;
		topRightBack.y = position.y + halfHeight;
		topRightBack.z = position.z - halfWidth;

		topLeftBack.x = position.x - halfWidth;
		topLeftBack.y = position.y + halfHeight;
		topLeftBack.z = position.z - halfWidth;

		halfWidthInternal = halfWidth;
		halfHeightInternal = halfHeight;
	}

	void moveCollider(glm::vec3& vector) {
		position = vector;
		buildAABBCollider(position, halfWidthInternal, halfHeightInternal);
	}
};