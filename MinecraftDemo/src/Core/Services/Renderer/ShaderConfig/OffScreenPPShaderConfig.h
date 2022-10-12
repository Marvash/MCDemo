#pragma once
#include "Core/Services/Renderer/Shader/Shader.h"
#include "Core/Services/Renderer/ShaderData/ShaderData.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include "Core/Textures/Texture.h"
#include "ShaderConfig.h"

class OffScreenPPShaderConfig : public ShaderConfig {
public:
	OffScreenPPShaderConfig(Shader* shader, Texture* screenTexture);
	void prepareShader(ModelData* modelData, ShaderData* shaderData) override;
	void useShaderConfig() override;
private:
	Texture* m_screenTexture;
};