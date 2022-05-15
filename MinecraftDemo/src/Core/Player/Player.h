#pragma once
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Cube/Cube.h"
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include "Core/Components/MovementComponent.h"
#include "Core/Events/Game/PlayerSelectedCubeChange.h"
#include <glm/glm.hpp>

class CoreServiceLocator;

class Player : public GameObject {
public:
	Player(CoreServiceLocator* coreServiceLocator);
	void onNotify(Event& newEvent) override;
	void update() override;
	Cube::CubeId getSelectedCube();
	Cube* getTargetCube();

private:
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();
	Cube* getFirstSolidCube();
	Cube* getLastPlaceableCube();
	Cube::CubeId m_selectedCubeId;
	Cube* m_targetCube;

	float m_jumpForce;
	float m_targetCubeRayLength;
};

