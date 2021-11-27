#include "AtlasManager.h"

AtlasManager* AtlasManager::singleton;

AtlasManager::AtlasManager() : atlasWidth(0), atlasHeight(0), textureOffset(0.000001f) {
	glGenTextures(1, &atlas);
}

void AtlasManager::loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames) {

	int width, height, nrChannels;
	std::stringstream completePath;
	int numMipMaps = mipMapFilenames.size();
	unsigned char* data;

	glBindTexture(GL_TEXTURE_2D, atlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, numMipMaps-1);

	stbi_set_flip_vertically_on_load(true);

	for (int i = 0; i < numMipMaps; i++) {
		completePath.str("");
		completePath << atlasBasePath << mipMapFilenames[i];
		data = stbi_load(completePath.str().c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum formatIn = GL_RGB;
			GLenum formatOut = GL_SRGB;
			if (nrChannels == 1) {
				formatIn = GL_RED;
				formatOut = GL_SRGB;
			}
			else if (nrChannels == 4) {
				formatIn = GL_RGBA;
				formatOut = GL_SRGB_ALPHA;
			}
			glTexImage2D(GL_TEXTURE_2D, i, formatOut, width, height, 0, formatIn, GL_UNSIGNED_BYTE, data);
			if (i == 0) {
				atlasWidth = width;
				atlasHeight = height;
			}
		}
		else
		{
			std::cout << "Failed to load texture " << completePath.str() << std::endl;
		}
		stbi_image_free(data);
	}
}

float AtlasManager::getCoordX(int spriteNum) {
	float spriteWidth = atlasWidth / numSpritesX;
	return (spriteWidth * spriteNum) / atlasWidth;
}

float AtlasManager::getCoordY(int spriteNum) {
	float spriteHeight = (atlasHeight / numSpritesY);
	return 1.0f - ((spriteHeight * spriteNum) / atlasHeight);
}

AtlasManager* AtlasManager::instance() {
	if (singleton == nullptr) {
		singleton = new AtlasManager();
	}
	return singleton;
}