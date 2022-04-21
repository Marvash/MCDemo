#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class BiomeColors {
public:
	BiomeColors();
	~BiomeColors();
	GLfloat* m_biomeColorsArray;
	const size_t TEX_COLORS_SIZE = 261;
};