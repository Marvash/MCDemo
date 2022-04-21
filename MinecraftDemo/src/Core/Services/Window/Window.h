#pragma once
#include "Core/Exceptions/WindowException.h"
#include "Core/Services/CoreService.h"
#include "Core/Events/WindowInitEvent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <boost/log/trivial.hpp>

class Window : public CoreService
{
public:
	Window(CoreEventDispatcher* eventDispatcher = nullptr);

	void init();

	GLFWwindow* getGlfwWindow();
	void updateWindow();
	void onNotify(Event& event) override;

private:
	const unsigned int openglVMajor = 4;
	const unsigned int openglVMinor = 2;

	const std::string windowName = "MinecraftDemo";

	unsigned int windowWidth;
	unsigned int windowHeight;

	GLFWwindow* glfwWindow;
};

