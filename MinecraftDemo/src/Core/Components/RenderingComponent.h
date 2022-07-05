#pragma once
#include "Core/Services/Renderer/ShaderData/ShaderData.h"
#include "Core/Services/Renderer/Shader/ShaderEnum.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderingComponent {
public:

	RenderingComponent();

	ShaderType m_shaderType;
	ShaderData* m_shaderData;
	ModelData m_modelData;
	bool m_enabled;
};