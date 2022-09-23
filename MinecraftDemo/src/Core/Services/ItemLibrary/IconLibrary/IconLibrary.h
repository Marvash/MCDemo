#pragma once
#include "Core/Textures/ImageTexture2D.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/Biome/BiomeLibrary.h"
#include "Core/Services/BlockLibrary/BlockLibrary.h"
#include "Core/Services/Atlas/Atlas.h"
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Boost/log/trivial.hpp>

class IconLibrary {
public:
    IconLibrary(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas, BlockLibrary* blockLibrary);
	~IconLibrary();
    ImageTexture2D* getItemIcon(ItemId itemId);

private:
	void generateBlockIcons();
	void generateItemIcons();
    void generateItemIcon(ItemId itemId);
    void addFaceTexIndexes(GLint* buffer, size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex);

    Renderer* m_renderer;
    Atlas* m_atlas;
    BiomeLibrary* m_biomeLibrary;
    BlockLibrary* m_blockLibrary;
	std::map<ItemId, ImageTexture2D*> m_itemIcons;
	GLint* m_cubeVerticesTexIndexes;
	GLint* m_itemVerticesTexIndexes;

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

    GLfloat m_iconItemVertices[18] = {
         0.5f, -0.5f,  0.0f, // bottom-right
        -0.5f,  0.5f,  0.0f, // top-left
        -0.5f, -0.5f,  0.0f, // bottom-left
        -0.5f,  0.5f,  0.0f, // top-left
         0.5f, -0.5f,  0.0f, // bottom-right
         0.5f,  0.5f,  0.0f, // top-right
    };
};