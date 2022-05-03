#pragma once
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Cube/Cube.h"
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include "Core/Components/MovementComponent.h"
#include <glm/glm.hpp>

class CoreServiceLocator;

class Player : public GameObject {
public:
	Player(CoreServiceLocator* coreServiceLocator);
	void onNotify(Event& newEvent) override;
	void update() override;
	void registerComponents() override;

private:
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();

	CoreServiceLocator* m_coreServiceLocator;
	Cube::CubeId m_selectedCubeId;
	MovementComponent m_movementComponent;

	float jumpForce;
};

