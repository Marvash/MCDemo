#include "WindowResizeEvent.h"

WindowResizeEvent::WindowResizeEvent(const unsigned int& windowWidth, const unsigned int& windowHeight) : 
	Event(EventType::WINDOW_RESIZE),
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight) {

}