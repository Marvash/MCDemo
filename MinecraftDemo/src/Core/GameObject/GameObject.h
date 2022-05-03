#pragma once
#include "Core/Events/Event.h"
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject();
	virtual void onNotify(Event& newEvent);
	virtual void update() = 0;
	virtual void registerComponents() = 0;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	unsigned int m_id;
protected:
	static unsigned int nextId;
};

