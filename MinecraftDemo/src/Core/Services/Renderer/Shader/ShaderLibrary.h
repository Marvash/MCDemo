#pragma once
#include "Shader.h"
#include "ShaderEnum.h"
#include <map>
#include <string>

class ShaderLibrary {
public:
	ShaderLibrary();
	void loadShader(const char* vshader, const char* fshader, ShaderType shaderType);
	Shader* getShader(ShaderType shaderType);
private:
	std::map<ShaderType, Shader*> m_shaders;
};