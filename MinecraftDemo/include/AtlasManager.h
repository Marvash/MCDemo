#pragma once
#include "coreInclude.h"
#include "Shader.h"
#include "Biomes/Biome.h"

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

	static int getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide);
	static int getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide);

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
	const size_t texDataSize = 288;
	const size_t colorDataSize = 261;

	AtlasManager();
	void loadTextureBuffer();
	void loadColorBuffer();
	void loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames);
	float getCoordX(int spriteNum);
	float getCoordY(int spriteNum);
};

