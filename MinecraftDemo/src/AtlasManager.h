#pragma once
#include "coreInclude.h"

class AtlasManager {
public:
	unsigned int atlas;
	const float textureOffset;

	static AtlasManager* instance();
	void loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames);
	float getCoordX(int spriteNum);
	float getCoordY(int spriteNum);
private:
	static AtlasManager* singleton;
	int atlasWidth;
	int atlasHeight;
	const int numSpritesX = 32;
	const int numSpritesY = 32;

	AtlasManager();
};

