#pragma once
#include "Core/Textures/ImageTexture2D.h"
#include "Core/Cube/Cube.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Boost/log/trivial.hpp>

class IconManager {
public:
	IconManager(CoreServiceLocator* coreServiceLocator);
	~IconManager();
    ImageTexture2D* getIcon(Cube::CubeId cubeId);

private:
	void generateIcons();
    void addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex);

	CoreServiceLocator* m_coreServiceLocator;
	std::map<Cube::CubeId, ImageTexture2D*> m_cubeIcons;
	GLint* m_verticesTexIndexes;

	GLfloat m_iconCubeVertices[108] = {
        // Back face
        -0.5f, -0.5f, -0.5f, // Bottom-left
         0.5f,  0.5f, -0.5f, // top-right
         0.5f, -0.5f, -0.5f, // bottom-right         
         0.5f,  0.5f, -0.5f, // top-right
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f,  0.5f, -0.5f, // top-left
        // Front face
         0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f,  0.5f,  0.5f, // top-left
        -0.5f, -0.5f,  0.5f, // bottom-left
        -0.5f,  0.5f,  0.5f, // top-left
         0.5f, -0.5f,  0.5f, // bottom-right
         0.5f,  0.5f,  0.5f, // top-right
        // Left face
        -0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f,  0.5f, -0.5f, // top-left
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f,  0.5f, -0.5f, // top-left
        -0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f,  0.5f,  0.5f, // top-right
        // Right face
         0.5f, -0.5f, -0.5f, // bottom-right
         0.5f,  0.5f,  0.5f, // top-left
         0.5f, -0.5f,  0.5f, // bottom-left 
         0.5f,  0.5f,  0.5f, // top-left
         0.5f, -0.5f, -0.5f, // bottom-right
         0.5f,  0.5f, -0.5f, // top-right 
        // Bottom face
         0.5f, -0.5f,  0.5f, // bottom-left
        -0.5f, -0.5f, -0.5f, // top-right
        -0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f, -0.5f, -0.5f, // top-right
         0.5f, -0.5f,  0.5f, // bottom-left
         0.5f, -0.5f, -0.5f, // top-left
        // Top face
         0.5f,  0.5f,  0.5f, // bottom-right
         -0.5f,  0.5f, -0.5f, // top-left
         -0.5f,  0.5f,  0.5f, // bottom-left   
         -0.5f,  0.5f, -0.5f, // top-left
         0.5f,  0.5f,  0.5f, // bottom-right
         0.5f,  0.5f, -0.5f, // top-right     
	};
};