#include "ImageTexture2D.h"

ImageTexture2D::ImageTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format) :
	Texture(GL_TEXTURE_2D),
	m_texWidth(width),
	m_texHeight(height) {
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_texWidth, m_texHeight, 0, format, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}