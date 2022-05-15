#pragma once
#include "Core/Events/Event.h"
#include "GameObjectTypeEnum.h"
#include "Core/Components/MovementComponent.h"
#include <glm/glm.hpp>

class CoreServiceLocator;

class GameObject
{
public:
	GameObject(CoreServiceLocator* coreServiceLocator, GameObjectType m_gameObjectType);
	virtual void onNotify(Event& newEvent);
	virtual void update() = 0;
	void registerComponents();
	void setMovementComponent(MovementComponent* moveComp);
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GameObjectType m_gameObjectType;
	unsigned int m_id;

	MovementComponent* m_movementComponent;
protected:
	static unsigned int nextId;
	CoreServiceLocator* m_coreServiceLocator;

	
};

