#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/EventTypeEnum.h"
#include <glm/glm.hpp>
#include <string>

class PlayerSelectedCubeChange : public Event {
public:
	PlayerSelectedCubeChange(std::string& name) :
		Event(EventType::PLAYER_SELECTED_CUBE_CHANGE),
		m_name(name) {
	}
	std::string m_name;
};