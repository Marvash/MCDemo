#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/EventTypeEnum.h"
#include <glm/glm.hpp>

class PlayerVelocityEvent : public Event {
public:
	PlayerVelocityEvent(glm::vec3& velocity) :
		Event(EventType::PLAYER_VELOCITY),
		m_velocity(velocity) {
	}
	glm::vec3 m_velocity;
};