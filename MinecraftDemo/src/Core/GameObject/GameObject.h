#pragma once
#include "Core/Events/Event.h"
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject();
	virtual void onNotify(Event& newEvent);
	virtual void update(float dt);
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	unsigned int m_id;
protected:
	static unsigned int nextId;
};

