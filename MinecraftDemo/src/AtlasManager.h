#pragma once
#include "coreInclude.h"
#include "Shader.h"

class AtlasManager {
public:
	GLuint atlas;
	GLuint texDataImage;
	GLuint colorDataImage;
	const float textureOffset;

	static AtlasManager* instance();
	void init();
	void setTextureShaderUniforms(Shader& shader);
	void bindTextures();

private:
	static AtlasManager* singleton;
	int atlasWidth;
	int atlasHeight;
	const int numSpritesX = 32;
	const int numSpritesY = 32;
	GLfloat* colorData;
	GLuint colorDataBuffer;
	GLfloat* texData;
	GLuint texDataBuffer;
	const size_t texDataSize = 216;
	const size_t colorDataSize = 252;

	AtlasManager();
	void loadTextureBuffer();
	void loadColorBuffer();
	void loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames);
	float getCoordX(int spriteNum);
	float getCoordY(int spriteNum);
};

