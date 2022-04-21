#include "MouseScrollEvent.h"

MouseScrollEvent::MouseScrollEvent(double& offsetX, double& offsetY) :
	Event(EventType::MOUSE_MOVE),
	m_offsetX(offsetX),
	m_offsetY(offsetY) {

}