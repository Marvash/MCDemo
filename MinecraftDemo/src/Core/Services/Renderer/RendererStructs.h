#pragma once
#include "Core/Services/Renderer/Shader/ShaderEnum.h"
#include "Core/Services/Renderer/ShaderData/ShaderData.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum class ProjectionType {
	ORTHOGRAPHIC,
	PERSPECTIVE
};

struct ModelData {
	GLuint VAO;
	unsigned int indexCount;
	glm::vec3 position;
};

struct ProjectionData {
	float near;
	float far;
};

struct OrthographicData : ProjectionData {
	float l;
	float r;
	float b;
	float t;
};

struct PerspectiveData : ProjectionData {
	float fov;
	float aspectRatio;
};

struct OffScreenRenderData {
	ModelData modelData;
	ShaderType shaderType;
	ShaderData* shaderData;
	glm::vec3 cameraDir;
	glm::vec3 cameraPos;
	ProjectionType projectionType;
	ProjectionData* projectionData;
	float width;
	float height;
};
