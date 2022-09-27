#pragma once
#include <glm/glm.hpp>

struct CameraRenderingData {
	float zoom;
	glm::mat4* viewMatrix;
	glm::vec3* position;
};