#include "ScreenShaderConfig.h"

ScreenShaderConfig::ScreenShaderConfig(Shader* shader, Texture* screenTexture) :
	ShaderConfig(shader),
	m_screenTexture(screenTexture) {

}

void ScreenShaderConfig::useShaderConfig() {
	m_screenTexture->bind(0);
	m_shader->use();
	m_shader->setInt("screenTexture", 0);
}

void ScreenShaderConfig::prepareShader(ModelData* modelData, ShaderData* shaderData) {
	m_shader->setFloat("exposure", 1.0f);
}