#pragma once
#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <vector>

class AtlasTexture : public Texture
{
public:
	AtlasTexture(std::vector<std::string>& atlasMipPaths);
	~AtlasTexture();

	void load();

	int m_atlasWidth, m_atlasHeight;
private:
	std::vector<std::string> m_atlasMipPaths;
};

