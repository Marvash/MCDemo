#pragma once
#include "Core/Services/Renderer/Shader/Shader.h"
#include "Core/Services/Renderer/ShaderData/ShaderData.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include "Core/Textures/Texture.h"
#include "ShaderConfig.h"

class ScreenShaderConfig : public ShaderConfig {
public:
	ScreenShaderConfig(Shader* shader, Texture* screenTexture);
	void prepareShader(ModelData* modelData, ShaderData* shaderData) override;
	void useShaderConfig() override;
private:
	Texture* m_screenTexture;
};