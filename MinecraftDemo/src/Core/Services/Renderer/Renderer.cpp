#include "Renderer.h"


Renderer::Renderer(CoreEventDispatcher* eventDispatcher) : 
	CoreService(eventDispatcher), 
	m_screenTexture(nullptr),
	m_msaaEnabled(true),
	m_msaaSamples(4),
	m_atlas(nullptr),
	m_biomeManager(nullptr),
	m_glfwWindow(nullptr),
	m_cameraRenderingData(nullptr) {
}

void Renderer::init() {
	BOOST_LOG_TRIVIAL(trace) << "Initializing renderer...";

	glGenFramebuffers(1, &m_msaaFramebuffer);
	glGenRenderbuffers(1, &m_msaaRbo);
	glGenFramebuffers(1, &m_intermediateFBO);
	glGenFramebuffers(1, &m_offScreenFramebuffer);
	glGenRenderbuffers(1, &m_offScreenRbo);
	glGenFramebuffers(1, &m_offScreenPPFramebuffer);
	m_offScreenTexture = new ImageTexture2D(m_screenWidth, m_screenHeight, GL_RGBA, GL_RGBA);
	m_offScreenPPTexture = new ImageTexture2D(m_screenWidth, m_screenHeight, GL_RGBA, GL_RGBA);
	m_msaaFBColorTexture = new MultisampleTexture2D(m_screenWidth, m_screenHeight, GL_RGBA16F, m_msaaSamples);
	m_screenTexture = new ImageTexture2D(m_screenWidth, m_screenHeight, GL_RGBA16F, GL_RGBA);

	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_offScreenTexture->m_id, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, m_offScreenRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_screenWidth, m_screenHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_offScreenRbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		BOOST_LOG_TRIVIAL(error) << "ERROR::FRAMEBUFFER:: Offscreen framebuffer is not complete! " << glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenPPFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_offScreenPPTexture->m_id, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		BOOST_LOG_TRIVIAL(error) << "ERROR::FRAMEBUFFER:: Offscreen PP framebuffer is not complete! " << glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	if (m_msaaEnabled) {
		msaaResize();
	}

	glGenVertexArrays(1, &m_screenQuadVAO);
	glGenBuffers(1, &m_screenQuadVBO);
	glBindVertexArray(m_screenQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_screenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_screenQuadVertices), &m_screenQuadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	m_shaderLibrary.loadShader("shaders/vDefaultShader.vert", "shaders/fDefaultShader.frag", ShaderType::WORLD);
	m_shaderLibrary.loadShader("shaders/vScreenShader.vert", "shaders/fScreenShader.frag", ShaderType::SCREEN);
	m_shaderLibrary.loadShader("shaders/vOffScreenPPShader.vert", "shaders/fOffScreenPPShader.frag", ShaderType::OFFSCREENPP);

	ScreenShaderConfig* screenShaderConfig = new ScreenShaderConfig(m_shaderLibrary.getShader(ShaderType::SCREEN), m_screenTexture);
	WorldShaderConfig* worldShaderConfig = new WorldShaderConfig(m_shaderLibrary.getShader(ShaderType::WORLD), m_atlas->getAtlasTexture(), m_atlas->getTexCoordsBuffer(), m_biomeManager->getBiomeColorsBuffer(), m_atlas->getSecondaryTexCoordsBuffer());
	OffScreenPPShaderConfig* offScreenPPShaderConfig = new OffScreenPPShaderConfig(m_shaderLibrary.getShader(ShaderType::OFFSCREENPP), m_offScreenTexture);

	m_shaderSetups.insert(std::make_pair<ShaderType, ShaderConfig*>(ShaderType::SCREEN, static_cast<ShaderConfig*>(screenShaderConfig)));
	m_shaderSetups.insert(std::make_pair<ShaderType, ShaderConfig*>(ShaderType::WORLD, static_cast<ShaderConfig*>(worldShaderConfig)));
	m_shaderSetups.insert(std::make_pair<ShaderType, ShaderConfig*>(ShaderType::OFFSCREENPP, static_cast<ShaderConfig*>(offScreenPPShaderConfig)));

	BOOST_LOG_TRIVIAL(trace) << "Renderer initialized!";

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 420 core");
}

void Renderer::deinit() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

float Renderer::getViewportWidth() {
	return m_screenWidth;
}

float Renderer::getViewportHeight() {
	return m_screenHeight;
}

void Renderer::setViewport(int posX, int posY, unsigned int width, unsigned int height) {
	glViewport(posX, posY, width, height);
}

void Renderer::registerComponent(RenderingComponent* renderingComponent) {
	m_componentsByType[renderingComponent->m_shaderType].push_back(renderingComponent);
}

void Renderer::msaaResize() {
	// TODO: Optimize risizing (if screen width and height smaller than some, do not resize and skip rendering)
	BOOST_LOG_TRIVIAL(info) << "Screen width: " << m_screenWidth << " screen height: " << m_screenHeight;
	m_msaaFBColorTexture->resetTexture(m_screenWidth, m_screenHeight, GL_RGBA16F, m_msaaSamples);
	glBindFramebuffer(GL_FRAMEBUFFER, m_msaaFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_msaaFBColorTexture->m_id, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, m_msaaRbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_msaaSamples, GL_DEPTH24_STENCIL8, m_screenWidth, m_screenHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_msaaRbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		BOOST_LOG_TRIVIAL(error) << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! " << glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_screenTexture->resetTexture(m_screenWidth, m_screenHeight, GL_RGBA16F, GL_RGBA);
	glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture->m_id, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Renderer::offscreenTextureResize(int width, int height) {
	m_offScreenTexture->resetTexture(width, height, GL_RGBA, GL_RGBA);
	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_offScreenTexture->m_id, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, m_offScreenRbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_offScreenRbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		BOOST_LOG_TRIVIAL(error) << "ERROR::FRAMEBUFFER:: Offscreen framebuffer is not complete! " << glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	m_offScreenPPTexture->resetTexture(width, height, GL_RGBA, GL_RGBA);
	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenPPFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_offScreenPPTexture->m_id, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		BOOST_LOG_TRIVIAL(error) << "ERROR::FRAMEBUFFER:: Offscreen PP framebuffer is not complete! " << glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::onNotify(Event& newEvent) {

	switch (newEvent.getEventType()) {
		case EventType::WINDOW_INIT: {
			WindowInitEvent* windowInitEvent = static_cast<WindowInitEvent*>(&newEvent);
			m_glfwWindow = windowInitEvent->m_window;
			m_screenWidth = windowInitEvent->m_width;
			m_screenHeight = windowInitEvent->m_height;
			setViewport(0, 0, m_screenWidth, m_screenHeight);
			break;
		}
		case EventType::WINDOW_RESIZE: {
			WindowResizeEvent* windowResizeEvent = static_cast<WindowResizeEvent*>(&newEvent);
			if (windowResizeEvent->m_windowWidth > 0 && windowResizeEvent->m_windowHeight > 0) {
				m_screenWidth = windowResizeEvent->m_windowWidth;
				m_screenHeight = windowResizeEvent->m_windowHeight;
				setViewport(0, 0, m_screenWidth, m_screenHeight);
				if (m_msaaEnabled) {
					msaaResize();
				}
			}
			break;
		}
	}
}

void Renderer::submitTexture(Texture* texture) {
	m_loadedTextures.insert(std::make_pair(texture->m_id, texture));
}

void Renderer::setClearColor(const glm::vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::setCameraRenderingData(CameraRenderingData* cameraRenderingData) {
	m_cameraRenderingData = cameraRenderingData;
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setAtlas(Atlas* atlas) {
	m_atlas = atlas;
}

void Renderer::setBiomeManager(BiomeLibrary* biomeManager) {
	m_biomeManager = biomeManager;
}

void Renderer::submitGUIElement(GUIElement* element) {
	m_submittedGUIElements.push_back(element);
}

void Renderer::clearSubmittedGUIElements() {
	m_submittedGUIElements.clear();
}

void Renderer::drawGUI() {
	for (auto& element : m_submittedGUIElements) {
		element->draw();
	}
}

void Renderer::drawChunks() {
	std::vector<RenderingComponent*>& componentList = m_componentsByType[ShaderType::WORLD];
	WorldShaderConfig* worldShaderConfig = static_cast<WorldShaderConfig*>(m_shaderSetups[ShaderType::WORLD]);
	worldShaderConfig->useShaderConfig();
	for (RenderingComponent* component : componentList) {
		if (component->m_enabled) {
			ModelData* modelData = &component->m_modelData;
			worldShaderConfig->setViewMatrix(m_cameraRenderingData->viewMatrix);
			glm::mat4 projection = glm::perspective(glm::radians(m_cameraRenderingData->zoom), (float)m_screenWidth / (float)m_screenHeight, 0.01f, 10000.0f);
			worldShaderConfig->setProjectionMatrix(&projection);
			worldShaderConfig->prepareShader(modelData, nullptr);
			glBindVertexArray(component->m_modelData.VAO);
			if (modelData->isIndexed) {
				glDrawElements(GL_TRIANGLES, component->m_modelData.indexCount, GL_UNSIGNED_INT, 0);
			}
			else {
				glDrawArrays(GL_TRIANGLES, 0, component->m_modelData.vertexCount);
			}
			glBindVertexArray(0);
		}
	}
}

void Renderer::draw() {
	if (m_msaaEnabled) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_msaaFramebuffer);
	}
	setClearColor(GAME_CLEAR_COLOR);
	clear();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	drawChunks();
	drawGUI();
	clearSubmittedGUIElements();
	//ImGui::ShowDemoWindow();

	if (m_msaaEnabled) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaaFramebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFBO);
		glBlitFramebuffer(0, 0, m_screenWidth, m_screenHeight, 0, 0, m_screenWidth, m_screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		setClearColor(SCREEN_CLEAR_COLOR);
		clear();
		ScreenShaderConfig* screenShaderConfig = static_cast<ScreenShaderConfig*>(m_shaderSetups[ShaderType::SCREEN]);
		screenShaderConfig->useShaderConfig();
		screenShaderConfig->prepareShader(nullptr, nullptr);
		glBindVertexArray(m_screenQuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

unsigned char* Renderer::drawOffScreen(OffScreenRenderData* renderData) {
	offscreenTextureResize(renderData->renderingWidth, renderData->renderingHeight);
	glViewport(0, 0, renderData->renderingWidth, renderData->renderingHeight);
	unsigned char* result = new unsigned char[renderData->renderingWidth * renderData->renderingHeight * 4];
	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenFramebuffer);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	setClearColor(renderData->clearColor);
	clear();
	switch (renderData->shaderType) {
		case ShaderType::WORLD: {
			WorldShaderConfig* worldShaderConfig = static_cast<WorldShaderConfig*>(m_shaderSetups[ShaderType::WORLD]);
			glm::mat4 view = glm::lookAt(renderData->cameraPos, renderData->cameraDir, WORLD_UP);
			worldShaderConfig->setViewMatrix(&view);
			glm::mat4 projection = glm::mat4(1.0f); 
			switch (renderData->projectionType) {
				case ProjectionType::ORTHOGRAPHIC: {
					OrthographicData* orthoData = static_cast<OrthographicData*>(renderData->projectionData);
					projection = glm::ortho(orthoData->l, orthoData->r, orthoData->b, orthoData->t, orthoData->near, orthoData->far);
					break;
				}
				case ProjectionType::PERSPECTIVE: {
					PerspectiveData* perspData = static_cast<PerspectiveData*>(renderData->projectionData);
					projection = glm::perspective(glm::radians(perspData->fov), perspData->aspectRatio, perspData->near, perspData->far);
					break;
				}
			}
			worldShaderConfig->setProjectionMatrix(&projection);
			worldShaderConfig->useShaderConfig();
			worldShaderConfig->prepareShader(&renderData->modelData, renderData->shaderData);
			BOOST_LOG_TRIVIAL(info) << "Shader prepared";
			glBindVertexArray(renderData->modelData.VAO);
			if (renderData->modelData.isIndexed) {
				glDrawElements(GL_TRIANGLES, renderData->modelData.indexCount, GL_UNSIGNED_INT, 0);
			}
			else {
				BOOST_LOG_TRIVIAL(info) << "about to render";
				glDrawArrays(GL_TRIANGLES, 0, renderData->modelData.vertexCount);
			}
			glBindVertexArray(0);
			break;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, m_offScreenPPFramebuffer);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	setClearColor(SCREEN_CLEAR_COLOR);
	clear();
	OffScreenPPShaderConfig* offScreenPPShaderConfig = static_cast<OffScreenPPShaderConfig*>(m_shaderSetups[ShaderType::OFFSCREENPP]);
	offScreenPPShaderConfig->useShaderConfig();
	offScreenPPShaderConfig->prepareShader(nullptr, nullptr);
	glBindVertexArray(m_screenQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_offScreenPPTexture->bind(0);
	BOOST_LOG_TRIVIAL(info) << "rendered, copying image";
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, result);
	BOOST_LOG_TRIVIAL(info) << "image copied";

	setViewport(0, 0, m_screenWidth, m_screenHeight);
	return result;
}