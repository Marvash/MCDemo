#include "Window.h"

Window::Window(CoreEventDispatcher* eventDispatcher) :
	CoreService(eventDispatcher), 
	glfwWindow(nullptr) {
}

void Window::init() {
	BOOST_LOG_TRIVIAL(trace) << "Initializing window...";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglVMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglVMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* glfwMode = glfwGetVideoMode(mainMonitor);
	windowWidth = glfwMode->width;
	windowHeight = glfwMode->height;
	glfwWindowHint(GLFW_RED_BITS, glfwMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, glfwMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, glfwMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, glfwMode->refreshRate);
	glfwWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	if (glfwWindow == nullptr)
	{
		std::string errorMessage = "Failed to create GLFW window";
		throw WindowException(errorMessage);
		glfwTerminate();
	}
	glfwSetWindowPos(glfwWindow, 0, 0);

	glfwMakeContextCurrent(glfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::string errorMessage = "Failed to initialize GLAD";
		throw WindowException(errorMessage);
	}
	WindowInitEvent event{ glfwWindow, windowWidth, windowHeight };
	notify(event);
	// tell GLFW to capture our mouse
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	BOOST_LOG_TRIVIAL(trace) << "Window intialized! Sending window init event...";
}

void Window::onNotify(Event& event) {

}

GLFWwindow* Window::getGlfwWindow() {
	if (glfwWindow == nullptr) {
		BOOST_LOG_TRIVIAL(warning) << "Accessing uninitialized glfw window";
	}
	return glfwWindow;
}

void Window::updateWindow() {
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
}