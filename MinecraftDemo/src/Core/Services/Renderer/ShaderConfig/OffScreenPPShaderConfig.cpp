#include "OffScreenPPShaderConfig.h"

OffScreenPPShaderConfig::OffScreenPPShaderConfig(Shader* shader, Texture* screenTexture) :
	ShaderConfig(shader),
	m_screenTexture(screenTexture) {

}

void OffScreenPPShaderConfig::useShaderConfig() {
	m_screenTexture->bind(0);
	m_shader->use();
	m_shader->setInt("screenTexture", 0);
}

void OffScreenPPShaderConfig::prepareShader(ModelData* modelData, ShaderData* shaderData) {
	m_shader->setFloat("exposure", 1.0f);
}