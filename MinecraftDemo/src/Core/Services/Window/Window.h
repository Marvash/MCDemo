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
	void deinit();

	GLFWwindow* getGlfwWindow();
	void updateWindow();
	void onNotify(Event& event) override;

private:
	const unsigned int openglVMajor = 4;
	const unsigned int openglVMinor = 2;

	const std::string m_windowName = "MinecraftDemo";

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	GLFWwindow* m_glfwWindow;
};

