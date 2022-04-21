#include "MultisampleTexture2D.h"

MultisampleTexture2D::MultisampleTexture2D(unsigned int width, unsigned int height, GLenum internalFormat, unsigned int numSamples) :
	Texture(GL_TEXTURE_2D),
	m_texWidth(width),
	m_texHeight(height) {
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_id);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, numSamples, internalFormat, m_texWidth, m_texHeight, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}