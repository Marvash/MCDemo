#pragma once
#include "Texture.h"

class ImageTexture2D : public Texture {
public:
	ImageTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format);
	ImageTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, void* data);
	void resetTexture(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format);
	void resetTexture(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, void* data);
private:
	unsigned int m_texWidth;
	unsigned int m_texHeight;
};