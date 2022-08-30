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
	Cube* getTargetCube();
	bool getIsOpenInventory();
	// TODO: Move getFirstSolidCube and getLastPlaceableCube in World or something (they do not belong in player)
	Cube* getFirstSolidCube();
	Cube* getLastPlaceableCube();

private:
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();
	void processInventoryKeyInput();
	void handleGameplayInput();
	void handleInventoryInput();
	void performNoItemPrimaryAction();
	Cube* m_targetCube;

	float m_jumpForce;
	float m_targetCubeRayLength;
	float m_lookSensitivity;
	int m_movementModeIndex;
	bool m_isOpenInventory;
};

