#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/EventTypeEnum.h"
#include <glm/glm.hpp>

class PlayerMoveEvent : public Event {
public:
	PlayerMoveEvent(glm::vec3& position) :
		Event(EventType::PLAYER_MOVE),
		m_position(position) {
	}
	glm::vec3 m_position;
};