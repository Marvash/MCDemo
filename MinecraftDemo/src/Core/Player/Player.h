#pragma once
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Services/BlockLibrary/Block.h"
#include "Core/Services/MovementSystem/MovementModeEnum.h"
#include "Core/Components/MovementComponent.h"
#include <glm/glm.hpp>

class CoreServiceLocator;

class Player : public GameObject {
public:
	Player(CoreServiceLocator* coreServiceLocator);
	void onNotify(Event& newEvent) override;
	void update() override;
	Block* getTargetBlock();
	bool getIsOpenInventory();
	float getTargetCubeRayLength();

private:
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();
	void processInventoryKeyInput();
	void handleGameplayInput();
	void handleInventoryInput();
	Block* m_targetBlock;
	

	float m_jumpForce;
	float m_targetCubeRayLength;
	float m_lookSensitivity;
	int m_movementModeIndex;
	bool m_isOpenInventory;
};

