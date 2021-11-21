#pragma once
#include "coreInclude.h"

class AtlasManager {
public:
	AtlasManager();
	void loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames);

	unsigned int atlas;
};

