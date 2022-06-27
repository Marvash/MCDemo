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
	m_chunkShader = new Shader("shaders/vDefaultShader.vs", "shaders/fDefaultShader.fs");
	m_screenShader = new Shader("shaders/vScreenShader.vs", "shaders/fScreenShader.fs");
	m_testCubeShader = new Shader("shaders/vShader.vs", "shaders/fShader.fs");
	m_screenShader->use();
	m_screenShader->setInt("screenTexture", 0);

	m_chunkShader->use();
	m_chunkShader->setInt("texAtlas", 0);
	m_chunkShader->setInt("vertexesTexData", 1);
	m_chunkShader->setInt("vertexesColorData", 2);

	glGenFramebuffers(1, &m_msaaFramebuffer);
	glGenRenderbuffers(1, &m_msaaRbo);
	glGenFramebuffers(1, &m_intermediateFBO);

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
	BOOST_LOG_TRIVIAL(trace) << "Renderer initialized!";

	glGenVertexArrays(1, &m_testCubeVAO);

	glBindVertexArray(m_testCubeVAO);

	glGenBuffers(1, &m_testCubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_testCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::GetIO().IniFilename = nullptr;

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

void Renderer::msaaResize() {
	if (m_msaaFBColorTexture != nullptr) {
		delete m_msaaFBColorTexture;
	}
	BOOST_LOG_TRIVIAL(info) << "Screen width: " << m_screenWidth << " screen height: " << m_screenHeight;
	m_msaaFBColorTexture = new MultisampleTexture2D(m_screenWidth, m_screenHeight, GL_RGBA16F, m_msaaSamples);
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

	if (m_screenTexture != nullptr) {
		delete m_screenTexture;
	}
	m_screenTexture = new ImageTexture2D(m_screenWidth, m_screenHeight, GL_RGBA16F, GL_RGBA);
	glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture->m_id, 0);
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
			m_screenWidth = windowResizeEvent->m_windowWidth;
			m_screenHeight = windowResizeEvent->m_windowHeight;
			setViewport(0, 0, m_screenWidth, m_screenHeight);
			if (m_msaaEnabled) {
				msaaResize();
			}
			break;
		}
	}
}

void Renderer::submitTexture(Texture* texture) {
	m_loadedTextures.insert(std::make_pair(texture->m_id, texture));
}

void Renderer::submitChunk(ChunkRenderData& data) {
	m_submittedChunks.insert(std::make_pair(data.VAO, data));
}

void Renderer::setClearColor(const glm::vec3& color) {
	glClearColor(color.r, color.g, color.b, 1.0f);
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

void Renderer::setBiomeManager(BiomeManager* biomeManager) {
	m_biomeManager = biomeManager;
}

void Renderer::bindGameTextures() {
	unsigned int nTextures = m_loadedTextures.size();
	unsigned int bindIndex = 0;
	if (m_atlas != nullptr) {
		m_atlas->getAtlasTexture()->bind(bindIndex);
		bindIndex++;
		m_atlas->getTexCoordsBuffer()->bind(bindIndex);
		bindIndex++;
	}
	if (m_biomeManager != nullptr) {
		m_biomeManager->getBiomeColorsBuffer()->bind(bindIndex);
		bindIndex++;
	}
	for (int i = 0; i < nTextures; i++) {
		m_loadedTextures.at(i)->bind(bindIndex);
		bindIndex++;
	}
	
	/*
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_atlas->getAtlasTexture()->m_id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, m_atlas->getTexCoordsBuffer()->m_id);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_BUFFER, m_biomeManager->getBiomeColorsBuffer()->m_id);
	*/
}

void Renderer::bindScreenTexture() {
	m_screenTexture->bind(0);
}

void Renderer::clearSubmittedChunks() {
	m_submittedChunks.clear();
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
	m_chunkShader->use();
	glm::mat4 projection = glm::perspective(glm::radians(m_cameraRenderingData->zoom), (float)m_screenWidth / (float)m_screenHeight, 0.01f, 10000.0f);
	glm::mat4 view = *m_cameraRenderingData->viewMatrix;
	for (auto& chunk : m_submittedChunks) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, chunk.second.position);
		glm::mat4 mvp = projection * view * model * glm::mat4(1.0f);
		m_chunkShader->setMat4("mvp", mvp);
		glBindVertexArray(chunk.first);
		glDrawElements(GL_TRIANGLES, chunk.second.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
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

	/*
	m_testCubeShader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->m_zoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 10000.0f);
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -10.0f));
	glm::mat4 mvp = projection * view * model * glm::mat4(1.0f);
	m_testCubeShader->setMat4("transform", mvp);
	glBindVertexArray(m_testCubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	*/

	bindGameTextures();
	drawChunks();
	clearSubmittedChunks();
	drawGUI();
	clearSubmittedGUIElements();

	if (m_msaaEnabled) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaaFramebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFBO);
		glBlitFramebuffer(0, 0, m_screenWidth, m_screenHeight, 0, 0, m_screenWidth, m_screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		setClearColor(SCREEN_CLEAR_COLOR);
		clear();
		m_screenShader->use();
		m_screenShader->setFloat("exposure", 1.0f);
		glBindVertexArray(m_screenQuadVAO);
		bindScreenTexture();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}