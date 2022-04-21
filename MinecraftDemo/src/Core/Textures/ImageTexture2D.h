#pragma once
#include "Texture.h"

class ImageTexture2D : public Texture {
public:
	ImageTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format);
private:
	unsigned int m_texWidth;
	unsigned int m_texHeight;
};