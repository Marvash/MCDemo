#include "WindowInitEvent.h"

WindowInitEvent::WindowInitEvent(GLFWwindow* window, unsigned int width, unsigned int height) :
	Event(EventType::WINDOW_INIT),
	m_window(window),
	m_width(width),
	m_height(height) {

}