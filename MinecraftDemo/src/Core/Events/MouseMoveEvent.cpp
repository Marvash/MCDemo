#include "MouseMoveEvent.h"

MouseMoveEvent::MouseMoveEvent(double& posX, double& posY) : 
	Event(EventType::MOUSE_MOVE),
	m_posX(posX),
	m_posY(posY) {

}