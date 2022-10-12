#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class AtlasTexCoordinates {
public:
	AtlasTexCoordinates(unsigned int atlasWidth, unsigned int atlasHeight);
	~AtlasTexCoordinates();
	GLfloat* m_atlasTexCoordinates;
	GLfloat* m_atlasSecondaryTexCoordinates;
	const size_t TEX_COORDINATES_SIZE = 624;
	const size_t SECONDARY_TEX_COORDINATES_SIZE = 80;

private:
	float getCoordX(int spriteNum);
	float getCoordY(int spriteNum);

	unsigned int m_atlasWidth, m_atlasHeight;
	const int NUM_SPRITES_X = 32;
	const int NUM_SPRITES_Y = 32;
};