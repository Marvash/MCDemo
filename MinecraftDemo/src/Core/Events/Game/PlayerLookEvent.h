#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/EventTypeEnum.h"
#include <glm/glm.hpp>

class PlayerLookEvent : public Event {
public:
	PlayerLookEvent(glm::vec3& direction) :
		Event(EventType::PLAYER_LOOK),
		m_direction(direction) {
	}
	glm::vec3 m_direction;
};