#pragma once
#include "coreInclude.h"

#include "Cube.h"

class ChunkManager;

class RayCast {
public:
	RayCast();
	static std::vector<Cube*> castRay(ChunkManager* manager, glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
};