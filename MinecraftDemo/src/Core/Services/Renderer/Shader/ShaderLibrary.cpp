#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary() {
	for (int i = 0; i < int(ShaderType::SCREEN); i++) {
		m_shaders[(ShaderType)i] = nullptr;
	}
}

void ShaderLibrary::loadShader(const char* vshader, const char* fshader, ShaderType shaderType) {
	Shader* shader = new Shader(vshader, fshader);
	m_shaders[shaderType] = shader;
}

Shader* ShaderLibrary::getShader(ShaderType shaderType) {
	return m_shaders[shaderType];
}