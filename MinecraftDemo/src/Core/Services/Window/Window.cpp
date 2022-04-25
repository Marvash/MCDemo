#include "Window.h"

Window::Window(CoreEventDispatcher* eventDispatcher) :
	CoreService(eventDispatcher), 
	m_glfwWindow(nullptr) {
}

void Window::init() {
	BOOST_LOG_TRIVIAL(trace) << "Initializing window...";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglVMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglVMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* glfwMode = glfwGetVideoMode(mainMonitor);
	m_windowWidth = glfwMode->width;
	m_windowHeight = glfwMode->height;
	glfwWindowHint(GLFW_RED_BITS, glfwMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, glfwMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, glfwMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, glfwMode->refreshRate);
	m_glfwWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName.c_str(), nullptr, nullptr);
	if (m_glfwWindow == nullptr)
	{
		std::string errorMessage = "Failed to create GLFW window";
		throw WindowException(errorMessage);
		glfwTerminate();
	}
	glfwSetWindowPos(m_glfwWindow, 0, 0);

	glfwMakeContextCurrent(m_glfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::string errorMessage = "Failed to initialize GLAD";
		throw WindowException(errorMessage);
	}
	WindowInitEvent event{ m_glfwWindow, m_windowWidth, m_windowHeight };
	notify(event);
	// tell GLFW to capture our mouse
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	BOOST_LOG_TRIVIAL(trace) << "Window intialized! Sending window init event...";
}

void Window::deinit() {
	glfwTerminate();
}

void Window::onNotify(Event& event) {

}

GLFWwindow* Window::getGlfwWindow() {
	if (m_glfwWindow == nullptr) {
		BOOST_LOG_TRIVIAL(warning) << "Accessing uninitialized glfw window";
	}
	return m_glfwWindow;
}

void Window::updateWindow() {
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
}