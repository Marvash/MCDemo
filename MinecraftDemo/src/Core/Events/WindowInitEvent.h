#pragma once
#include "Event.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class WindowInitEvent : public Event
{
public:
	WindowInitEvent(GLFWwindow* window, unsigned int width, unsigned int height);

	GLFWwindow* m_window;
	unsigned int m_width;
	unsigned int m_height;
};

