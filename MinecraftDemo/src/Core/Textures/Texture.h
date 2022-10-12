#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Texture
{
public:
	Texture(GLenum textureType);
	virtual ~Texture();
	virtual void bind(unsigned int unit);

	GLuint m_id;
	GLenum m_textureType;
};