#include "TextureBuffer.h"

TextureBuffer::TextureBuffer(GLfloat* texData, unsigned int dataSize) : 
	Texture(GL_TEXTURE_BUFFER),
	m_texData(texData),
	m_dataSize(dataSize) {
	glGenBuffers(1, &m_bufferId);
	load();
}

void TextureBuffer::load() {
	glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * m_dataSize, m_texData, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
	glBindTexture(GL_TEXTURE_BUFFER, m_id);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, m_bufferId);
	glBindTexture(GL_TEXTURE_BUFFER, 0);
};

TextureBuffer::~TextureBuffer() {
	glDeleteBuffers(1, &m_bufferId);
}