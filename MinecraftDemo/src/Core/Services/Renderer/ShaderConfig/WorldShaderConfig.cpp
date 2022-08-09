#include "WorldShaderConfig.h"

WorldShaderConfig::WorldShaderConfig(Shader* shader, Texture* atlasTexture, Texture* texCoords, Texture* biomeColors) : 
	ShaderConfig(shader),
	m_atlasTexture(atlasTexture),
	m_vertexTexCoords(texCoords),
	m_vertexTexColor(biomeColors) {
}

void WorldShaderConfig::useShaderConfig() {
	m_atlasTexture->bind(0);
	m_vertexTexCoords->bind(1);
	m_vertexTexColor->bind(2);
	m_shader->use();
	m_shader->setInt("texAtlas", 0);
	m_shader->setInt("vertexesTexData", 1);
	m_shader->setInt("vertexesColorData", 2);
}

void WorldShaderConfig::prepareShader(ModelData* modelData, ShaderData* shaderData) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, modelData->position);
	glm::mat4 mvp = (*m_projectionMatrix) * (*m_viewMatrix) * model * glm::mat4(1.0f);
	m_shader->setMat4("mvp", mvp);
}

void WorldShaderConfig::setViewMatrix(glm::mat4* viewMatrix) {
	m_viewMatrix = viewMatrix;
}

void WorldShaderConfig::setProjectionMatrix(glm::mat4* projectionMatrix) {
	m_projectionMatrix = projectionMatrix;
}

void WorldShaderConfig::setAtlasTexture(Texture* texture) {
	m_atlasTexture = texture;
}

void WorldShaderConfig::setTexCoordsTexture(Texture* texture) {
	m_vertexTexCoords = texture;
}

void WorldShaderConfig::setTexColorTexture(Texture* texture) {
	m_vertexTexColor = texture;
}