#pragma once
#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TextureBuffer : public Texture
{
public:
	TextureBuffer(GLfloat* texData, unsigned int dataSize);
	~TextureBuffer();

	void load();
private:
	GLuint m_bufferId;
	GLfloat* m_texData;
	unsigned int m_dataSize;
};

