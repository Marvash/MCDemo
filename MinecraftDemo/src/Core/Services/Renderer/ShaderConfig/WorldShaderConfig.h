#pragma once
#include "Core/Services/Renderer/Shader/Shader.h"
#include "Core/Textures/Texture.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include "ShaderConfig.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class WorldShaderConfig : public ShaderConfig {
public:
	WorldShaderConfig(Shader* shader, Texture* atlasTexture, Texture* texCoords, Texture* biomeColors, Texture* secondaryTexCoords);
	void prepareShader(ModelData* modelData, ShaderData* shaderData) override;
	void setViewMatrix(glm::mat4* viewMatrix);
	void setProjectionMatrix(glm::mat4* projectionMatrix);
	void setAtlasTexture(Texture* texture);
	void setTexCoordsTexture(Texture* texture);
	void setTexColorTexture(Texture* texture);
	void useShaderConfig() override;
private:
	Texture* m_atlasTexture;
	Texture* m_vertexTexCoords;
	Texture* m_vertexTexColor;
	Texture* m_vertexSecondaryTexCoords;
	glm::mat4* m_viewMatrix;
	glm::mat4* m_projectionMatrix;
};