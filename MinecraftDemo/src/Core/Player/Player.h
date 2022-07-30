#pragma once
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Cube/Cube.h"
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include "Core/Components/MovementComponent.h"
#include "Core/InventoryManager/InventoryManager.h"
#include <glm/glm.hpp>

class CoreServiceLocator;

class Player : public GameObject {
public:
	Player(CoreServiceLocator* coreServiceLocator);
	void onNotify(Event& newEvent) override;
	void update() override;
	Item* getSelectedItem();
	Cube* getTargetCube();
	InventoryManager* getInventoryManager();

private:
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();
	Cube* getFirstSolidCube();
	Cube* getLastPlaceableCube();
	Cube* m_targetCube;
	InventoryManager m_inventoryManager;

	float m_jumpForce;
	float m_targetCubeRayLength;
	float m_lookSensitivity;
	int m_movementModeIndex;
};

