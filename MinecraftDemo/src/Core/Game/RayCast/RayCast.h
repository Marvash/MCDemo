#pragma once
#include "Core/Game/Cube/Cube.h"
#include <vector>
#include <glm/glm.hpp>

class ChunkManager;

class RayCast {
public:
	RayCast();
	static std::vector<Cube*> castRay(ChunkManager* manager, glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
};