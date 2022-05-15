#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/WindowInitEvent.h"
#include "Core/Events/WindowResizeEvent.h"
#include "Core/Services/CoreService.h"
#include "Core/Textures/Texture.h"
#include "Core/Shaders/Shader.h"
#include "Core/Exceptions/RendererException.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Textures/ImageTexture2D.h"
#include "Core/Textures/MultisampleTexture2D.h"
#include "Core/Services/CameraSystem/CameraRenderingData.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Core/GUI/GUIElement.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

class Renderer : public CoreService
{

public:
	Renderer(CoreEventDispatcher* eventDispatcher);

	void onNotify(Event& newEvent) override;
	void submitTexture(Texture* texture);
	void bindGameTextures();
	void bindScreenTexture();
	void setAtlas(Atlas* atlas);
	void setBiomeManager(BiomeManager* biomeManager);
	void drawChunks();
	void drawGUI();
	void clearSubmittedChunks();
	void clearSubmittedGUIElements();
	void setClearColor(const glm::vec3& color);
	void clear();
	void submitChunk(ChunkRenderData& data);
	void submitGUIElement(GUIElement* element);
	void setCameraRenderingData(CameraRenderingData* cameraRenderingData);
	void draw();
	void init();
	void deinit();
private:
	void setViewport(int posX, int posY, unsigned int width, unsigned int height);
	void msaaResize();

	GLFWwindow* m_glfwWindow;
	Shader* m_chunkShader;
	Shader* m_screenShader;
	Shader* m_testCubeShader;
	Atlas* m_atlas;
	BiomeManager* m_biomeManager;
	ImageTexture2D* m_screenTexture;
	GLuint m_intermediateFBO;
	MultisampleTexture2D* m_msaaFBColorTexture;
	GLuint m_msaaFramebuffer;
	GLuint m_msaaRbo;
	GLuint m_screenQuadVAO, m_screenQuadVBO;
	GLuint m_testCubeVAO, m_testCubeVBO;
	CameraRenderingData* m_cameraRenderingData;
	float m_screenQuadVertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	float vertices[180] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int m_screenWidth, m_screenHeight;
	std::map<GLuint, Texture*> m_loadedTextures;
	std::map<GLuint, ChunkRenderData> m_submittedChunks;
	std::vector<GUIElement*> m_submittedGUIElements;

	unsigned int m_msaaSamples;
	bool m_msaaEnabled;
	const glm::vec3 GAME_CLEAR_COLOR = glm::vec3(0.08f, 0.9f, 0.95f);
	const glm::vec3 SCREEN_CLEAR_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
};