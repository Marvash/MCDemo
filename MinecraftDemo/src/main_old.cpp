//#define STB_IMAGE_IMPLEMENTATION
//
//#include "coreInclude.h"
//
//#include "Shader.h"
//#include "Camera.h"
//#include "AtlasManager.h"
//#include "ChunkManager.h"
//#include "Cube.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//void processInput(GLFWwindow* window);
//void toggleSpeedBoost(bool on);
//void testFunc(bool on);
//
//Camera camera(glm::vec3(0.0f, 2.0f, 0.0f));
//ChunkManager chunkManager(glm::vec3(0.0f, 0.0f, 0.0f));
//
//float lastX = 0.0f;
//float lastY = 0.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//float exposure = 1.0f;
//
//Cube::CubeId selectedCubeId(Cube::CubeId::DIRT_BLOCK);
//
//int main() {
//
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
//	const GLFWvidmode* mode = glfwGetVideoMode(mainMonitor);
//	int swidth, sheight;
//	swidth = mode->width;
//	sheight = mode->height;
//	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
//	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
//	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
//	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
//	GLFWwindow* window = glfwCreateWindow(swidth, sheight, "MinecraftDemo", nullptr, nullptr);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwSetWindowPos(window, 0, 0);
//
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glViewport(0, 0, mode->width, mode->height);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	lastX = mode->width / 2.0f;
//	lastY = mode->height / 2.0f;
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	unsigned int msaaFramebuffer;
//	glGenFramebuffers(1, &msaaFramebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
//	unsigned int textureColorBufferMultiSampled;
//	glGenTextures(1, &textureColorBufferMultiSampled);
//	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
//	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, mode->width, mode->height, GL_TRUE);
//	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);
//	unsigned int msaaRbo;
//	glGenRenderbuffers(1, &msaaRbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, msaaRbo);
//	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, mode->width, mode->height);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, msaaRbo);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	unsigned int intermediateFBO;
//	glGenFramebuffers(1, &intermediateFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
//	unsigned int screenTexture;
//	glGenTextures(1, &screenTexture);
//	glBindTexture(GL_TEXTURE_2D, screenTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mode->width, mode->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);	// we only need a color buffer
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//		std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << std::endl;
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	float screenQuadVertices[] = {
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		-1.0f, -1.0f,  0.0f, 0.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//		 1.0f,  1.0f,  1.0f, 1.0f
//	};
//
//	unsigned int screenQuadVAO, screenQuadVBO;
//	glGenVertexArrays(1, &screenQuadVAO);
//	glGenBuffers(1, &screenQuadVBO);
//	glBindVertexArray(screenQuadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadVertices), &screenQuadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); 
//
//	Shader defaultShader("shaders/vDefaultShader.vs", "shaders/fDefaultShader.fs");
//	Shader screenShader("shaders/vScreenShader.vs", "shaders/fScreenShader.fs");
//	screenShader.setInt("screenTexture", 0);
//
//	AtlasManager* mainAtlas = AtlasManager::instance();
//	mainAtlas->init();
//	defaultShader.use();
//	mainAtlas->setTextureShaderUniforms(defaultShader);
//
//	chunkManager.startGeneratorThreads();
//	chunkManager.startBuilderThreads();
//
//	float highestDelta = 0.0f;
//	while (!glfwWindowShouldClose(window)) {
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		int screenWidth, screenHeight;
//		glfwGetWindowSize(window, &screenWidth, &screenHeight);
//		
//		chunkManager.updateGenerationOrigin(camera.Position, camera.Front);
//
//		glViewport(0, 0, screenWidth, screenHeight);
//		glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
//		glClearColor(0.08f, 0.9f, 0.95f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_CULL_FACE);
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 10000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//
//		defaultShader.use();
//		mainAtlas->bindTextures();
//
//		chunkManager.reloadChunks();
//		chunkManager.drawChunks(defaultShader, projection, view);
//
//		glDisable(GL_DEPTH_TEST);
//
//		glBindFramebuffer(GL_READ_FRAMEBUFFER, msaaFramebuffer);
//		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
//		glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, screenWidth, screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glDisable(GL_CULL_FACE);
//
//		screenShader.use();
//		screenShader.setFloat("exposure", exposure);
//		glBindVertexArray(screenQuadVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, screenTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void testFunc(bool on) {
//	static bool wasOn = false;
//	if (!wasOn && on) {
//		float height = chunkManager.terrainGen.getHeight(camera.Position.x, camera.Position.z);
//		std::cout << "Final height is: " << height << std::endl;
//		wasOn = true;
//	} else if (wasOn && !on) {
//		wasOn = false;
//	}
//}
//
//void toggleSpeedBoost(bool on) {
//	static bool wasOn = false;
//	if (!wasOn && on) {
//		camera.MovementSpeed = camera.MovementSpeed * 2.0f;
//		wasOn = true;
//	}
//	else if(wasOn && !on) {
//		camera.MovementSpeed = camera.MovementSpeed / 2.0f;
//		wasOn = false;
//	}
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//		exposure += (1.0f * deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//		exposure -= (1.0f * deltaTime);
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
//		selectedCubeId = Cube::CubeId::SAND_BLOCK;
//	}
//	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
//		selectedCubeId = Cube::CubeId::DIRT_BLOCK;
//	}
//	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
//		selectedCubeId = Cube::CubeId::STONE_BLOCK;
//	}
//	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
//		selectedCubeId = Cube::CubeId::OAK_LOG;
//	}
//	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
//		selectedCubeId = Cube::CubeId::LEAVES;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
//		toggleSpeedBoost(true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
//		toggleSpeedBoost(false);
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
//		testFunc(true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
//		testFunc(false);
//	}
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset, false);
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//		chunkManager.destroyBlock();
//	}
//	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
//		chunkManager.placeBlock(selectedCubeId);
//	}
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}