#include "MouseButtonEvent.h"

MouseButtonEvent::MouseButtonEvent(InputMouseButton button, InputAction action) :
	Event(EventType::MOUSE_BUTTON),
	m_button(button),
	m_action(action) {

}