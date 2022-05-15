#pragma once
#include "Core/Cube/Cube.h"
#include <vector>
#include <glm/glm.hpp>

class ChunkManager;

class RayCast {
public:
	RayCast();
	static std::vector<Cube*> castRay(ChunkManager* manager, glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
	static void castRay(ChunkManager* manager, glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength, std::vector<Cube*>& cubes);
};