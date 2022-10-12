#pragma once
#include "Core/Services/Renderer/ShaderData/ShaderData.h"
#include "Core/Services/Renderer/RendererStructs.h"

class ShaderConfig {
public:
	ShaderConfig(Shader* shader) : m_shader(shader) {};
	virtual void prepareShader(ModelData* modelData, ShaderData* shaderData) = 0;
	virtual void useShaderConfig() = 0;
protected:
	Shader* m_shader;
};