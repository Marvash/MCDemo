#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/WindowInitEvent.h"
#include "Core/Events/WindowResizeEvent.h"
#include "Core/Services/CoreService.h"
#include "Core/Textures/Texture.h"
#include "Core/Services/Renderer/Shader/Shader.h"
#include "Core/Services/Renderer/ShaderConfig/ShaderConfig.h"
#include "Core/Services/Renderer/Shader/ShaderLibrary.h"
#include "Core/Services/Renderer/ShaderConfig/WorldShaderConfig.h"
#include "Core/Services/Renderer/ShaderConfig/ScreenShaderConfig.h"
#include "Core/Services/Renderer/ShaderConfig/OffScreenPPShaderConfig.h"
#include "Core/Components/RenderingComponent.h"
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/Biome/BiomeLibrary.h"
#include "Core/Exceptions/RendererException.h"
#include "Core/Textures/ImageTexture2D.h"
#include "Core/Textures/MultisampleTexture2D.h"
#include "Core/Services/CameraSystem/CameraRenderingData.h"
#include "Core/Services/Renderer/RendererStructs.h" 
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
	void setAtlas(Atlas* atlas);
	void setBiomeManager(BiomeLibrary* biomeManager);
	void drawChunks();
	void drawGUI();
	void clearSubmittedGUIElements();
	void setClearColor(const glm::vec4& color);
	void clear();
	void submitGUIElement(GUIElement* element);
	void setCameraRenderingData(CameraRenderingData* cameraRenderingData);
	void draw();
	void init();
	void deinit();
	void registerComponent(RenderingComponent* renderingComponent);
	float getViewportWidth();
	float getViewportHeight();
	unsigned char* drawOffScreen(OffScreenRenderData* renderData);
	
private:
	void setViewport(int posX, int posY, unsigned int width, unsigned int height);
	void msaaResize();
	void offscreenTextureResize(int width, int height);

	GLFWwindow* m_glfwWindow;
	ShaderLibrary m_shaderLibrary;
	Atlas* m_atlas;
	BiomeLibrary* m_biomeManager;
	ImageTexture2D* m_screenTexture;
	GLuint m_intermediateFBO;
	MultisampleTexture2D* m_msaaFBColorTexture;
	GLuint m_msaaFramebuffer;
	GLuint m_msaaRbo;
	GLuint m_screenQuadVAO, m_screenQuadVBO;
	GLuint m_testCubeVAO, m_testCubeVBO;
	CameraRenderingData* m_cameraRenderingData;
	ImageTexture2D* m_offScreenTexture;
	ImageTexture2D* m_offScreenPPTexture;
	GLuint m_offScreenFramebuffer;
	GLuint m_offScreenRbo;
	GLuint m_offScreenPPFramebuffer;
	float m_screenQuadVertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	
	unsigned int m_screenWidth, m_screenHeight;
	std::map<GLuint, Texture*> m_loadedTextures;
	std::vector<GUIElement*> m_submittedGUIElements;
	std::map<ShaderType, ShaderConfig*> m_shaderSetups;
	std::map<ShaderType, std::vector<RenderingComponent*>> m_componentsByType;

	unsigned int m_msaaSamples;
	bool m_msaaEnabled;
	const glm::vec4 GAME_CLEAR_COLOR = glm::vec4(0.08f, 0.9f, 0.95f, 1.0f);
	const glm::vec4 SCREEN_CLEAR_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
};