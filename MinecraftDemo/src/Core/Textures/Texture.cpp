#include "Texture.h"

Texture::Texture(GLenum textureType) : m_textureType(textureType) {
	glGenTextures(1, &m_id);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

void Texture::bind(unsigned int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(m_textureType, m_id);
}