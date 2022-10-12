#pragma once
#include "Texture.h"

class MultisampleTexture2D : public Texture {
public:
	MultisampleTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, unsigned int numSamples);
	void resetTexture(unsigned int width, unsigned int height, GLenum internalFormat, unsigned int numSamples);
private:
	unsigned int m_texWidth;
	unsigned int m_texHeight;
};