#pragma once
#include <glm/glm.hpp>

struct CameraRenderingData {
	float zoom;
	glm::mat4* viewMatrix;
};