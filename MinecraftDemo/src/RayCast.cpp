#include "RayCast.h"

#include "ChunkManager.h"

RayCast::RayCast() {

}

std::vector<Cube*> RayCast::castRay(ChunkManager* manager, glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength) {
	glm::vec3 rayDirNorm = glm::normalize(rayDirection);
	glm::vec3 xRayDirAux, yRayDirAux, zRayDirAux;
	xRayDirAux.x = 1.0f;
	xRayDirAux.y = (1.0f / rayDirNorm.x) * rayDirNorm.y;
	xRayDirAux.z = (1.0f / rayDirNorm.x) * rayDirNorm.z;
	yRayDirAux.x = (1.0f / rayDirNorm.y) * rayDirNorm.x;
	yRayDirAux.y = 1.0f;
	yRayDirAux.z = (1.0f / rayDirNorm.y) * rayDirNorm.z;
	zRayDirAux.x = (1.0f / rayDirNorm.z) * rayDirNorm.x;
	zRayDirAux.y = (1.0f / rayDirNorm.z) * rayDirNorm.y;
	zRayDirAux.z = 1.0f;
	glm::vec3 ray = (rayOrigin + (rayDirection * rayLength)) - rayOrigin;
	float xDir = glm::sign(ray.x);
	float yDir = glm::sign(ray.y);
	float zDir = glm::sign(ray.z);
	std::vector<Cube*> cubes;
	Cube* startingCube = manager->getCubeByCoords(rayOrigin);
	if (startingCube != nullptr) {
		cubes.push_back(startingCube);
	}
	glm::vec3 xRay(0.0f, 0.0f, 0.0f);
	glm::vec3 yRay(0.0f, 0.0f, 0.0f);
	glm::vec3 zRay(0.0f, 0.0f, 0.0f);
	glm::vec3 originBlockCoords(glm::floor(rayOrigin.x), glm::floor(rayOrigin.y), glm::floor(rayOrigin.z));
	float mainAxisDelta = 0.0f;
	if (xDir > 0.0f) {
		mainAxisDelta = 1.0f - (rayOrigin.x - originBlockCoords.x);
	}
	else {
		mainAxisDelta = rayOrigin.x - originBlockCoords.x;
	}
	xRay.x += xRayDirAux.x * mainAxisDelta;
	xRay.y += xRayDirAux.y * mainAxisDelta;
	xRay.z += xRayDirAux.z * mainAxisDelta;
	if (yDir > 0.0f) {
		mainAxisDelta = 1.0f - (rayOrigin.y - originBlockCoords.y);
	}
	else {
		mainAxisDelta = rayOrigin.y - originBlockCoords.y;
	}
	yRay.x += yRayDirAux.x * mainAxisDelta;
	yRay.y += yRayDirAux.y * mainAxisDelta;
	yRay.z += yRayDirAux.z * mainAxisDelta;
	if (zDir > 0.0f) {
		mainAxisDelta = 1.0f - (rayOrigin.z - originBlockCoords.z);
	}
	else {
		mainAxisDelta = rayOrigin.z - originBlockCoords.z;
	}
	zRay.x += zRayDirAux.x * mainAxisDelta;
	zRay.y += zRayDirAux.y * mainAxisDelta;
	zRay.z += zRayDirAux.z * mainAxisDelta;

	while (cubes.size() > 0) {
		if (glm::length(xRay) >= rayLength && glm::length(yRay) >= rayLength && glm::length(zRay) >= rayLength) {
			break;
		}
		float minRayLength = glm::min(glm::min(glm::length(xRay), glm::length(yRay)), glm::length(zRay));
		if (minRayLength == glm::length(xRay)) {
			xRay.x += xRayDirAux.x;
			xRay.y += xRayDirAux.y;
			xRay.z += xRayDirAux.z;
			Cube::FaceSide side = Cube::FaceSide::RIGHT;
			if (xDir < 0.0f) {
				side = Cube::FaceSide::LEFT;
			}
			cubes.push_back(cubes.at(cubes.size() - 1)->chunkRef->findNeighbourBlock(side, cubes.at(cubes.size() - 1)));
		}
		else if (minRayLength == glm::length(yRay)) {
			yRay.x += yRayDirAux.x;
			yRay.y += yRayDirAux.y;
			yRay.z += yRayDirAux.z;
			Cube::FaceSide side = Cube::FaceSide::TOP;
			if (yDir < 0.0f) {
				side = Cube::FaceSide::BOTTOM;
			}
			cubes.push_back(cubes.at(cubes.size() - 1)->chunkRef->findNeighbourBlock(side, cubes.at(cubes.size() - 1)));
		}
		else {
			zRay.x += zRayDirAux.x;
			zRay.y += zRayDirAux.y;
			zRay.z += zRayDirAux.z;
			Cube::FaceSide side = Cube::FaceSide::FRONT;
			if (zDir < 0.0f) {
				side = Cube::FaceSide::BACK;
			}
			cubes.push_back(cubes.at(cubes.size() - 1)->chunkRef->findNeighbourBlock(side, cubes.at(cubes.size() - 1)));
		}
	}
	return cubes;
}