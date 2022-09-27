#include "Player.h"
#include "Core/Services/CoreServiceLocator.h"

Player::Player(CoreServiceLocator* coreServiceLocator) : GameObject(coreServiceLocator, GameObjectType::DYNAMIC),
	m_jumpForce(9.0f), // 8.2f
	m_targetBlock(nullptr),
	m_targetCubeRayLength(10.0f),
	m_lookSensitivity(0.02f),
	m_movementModeIndex((int)MovementMode::FLY),
	m_isOpenInventory(false) {
	setMovementComponent(new MovementComponent());
	m_position = glm::vec3(112.5f, 2.5f, -44.5f);
	//m_position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_movementComponent->setMovementSpeed(4.0f);
	m_movementComponent->setFlySpeed(15.0f);
	m_movementComponent->setColliderHalfHeight(0.9f);
	m_movementComponent->setColliderHalfWidth(0.3f);
	m_coreServiceLocator->getCameraSystem()->setPlayerPosition(m_position);
	m_coreServiceLocator->getWorld()->updateGenerationOrigin(m_position);
	registerComponents();
	m_coreServiceLocator->getMovementSystem()->setMovementMode(this, MovementMode::FLY);
	m_coreServiceLocator->getGameObjectManager()->setPlayerId(m_id);

	Inventory* inventory = m_coreServiceLocator->getInventory();

	inventory->addItemInEmptyInventorySlot(ItemId::DIRT_BLOCK_ITEM, 10, inventory->getInventorySlots());
	inventory->addItemInEmptyInventorySlot(ItemId::STONE_BLOCK_ITEM, 10, inventory->getInventorySlots() + 1);
	inventory->addItemInEmptyInventorySlot(ItemId::SAND_BLOCK_ITEM, 10, inventory->getInventorySlots() + 2);
	inventory->addItemInEmptyInventorySlot(ItemId::PLANK_BLOCK_ITEM, 10, inventory->getInventorySlots() + 3);
	inventory->addItemInEmptyInventorySlot(ItemId::STICK, 10, inventory->getInventorySlots() + 4);
	inventory->setItemBarSelectedSlot(0);
}

void Player::onNotify(Event& newEvent) {
}

void Player::processMousePosition() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float xoffset = (float)inputManager->getMouseXDelta() * m_lookSensitivity;
	float yoffset = (float)inputManager->getMouseYDelta() * m_lookSensitivity;
	m_coreServiceLocator->getCameraSystem()->processMouseMovement(xoffset, yoffset, true);
}

void Player::processMouseScroll() {
	Inventory* inventory = m_coreServiceLocator->getInventory();
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float yoffset = (float)inputManager->getScrollYDelta();
	if (yoffset != 0.0f) {
		unsigned int selectedSlot = inventory->getItemBarSelectedSlot();
		if (selectedSlot == 0 && glm::sign(yoffset) > 0.0f) {
			selectedSlot = inventory->ITEMBAR_SLOTS - 1;
		}
		else {
			selectedSlot -= (unsigned int)glm::sign(yoffset);
			selectedSlot = selectedSlot % inventory->ITEMBAR_SLOTS;
		}
		inventory->setItemBarSelectedSlot(selectedSlot);
	}
	//m_coreServiceLocator->getCameraSystem()->processMouseScroll(yoffset);
}

void Player::processKeyinput() {
	Inventory* inventory = m_coreServiceLocator->getInventory();
	InputManager* inputManager = m_coreServiceLocator->getInput();
	double dt = m_coreServiceLocator->getApplicationManager()->getDeltaTime();
	/*
	if (inputManager->getInputState(InputKey::KEY_W)) { 
		m_camera->processKeyboard(CameraMovement::FORWARD, dt);
	}
	if (inputManager->getInputState(InputKey::KEY_A)) {
		m_camera->processKeyboard(CameraMovement::LEFT, dt);
	}
	if (inputManager->getInputState(InputKey::KEY_S)) {
		m_camera->processKeyboard(CameraMovement::BACKWARD, dt);
	}
	if (inputManager->getInputState(InputKey::KEY_D)) {
		m_camera->processKeyboard(CameraMovement::RIGHT, dt);
	}
	*/
	glm::vec3 inputVelocity(0.0f, 0.0f, 0.0f);
	if (inputManager->getInputState(InputKey::KEY_W)) {
		inputVelocity += m_coreServiceLocator->getCameraSystem()->m_front;
	}
	if (inputManager->getInputState(InputKey::KEY_A)) {
		inputVelocity -= m_coreServiceLocator->getCameraSystem()->m_right;
	}
	if (inputManager->getInputState(InputKey::KEY_S)) {
		inputVelocity -= m_coreServiceLocator->getCameraSystem()->m_front;
	}
	if (inputManager->getInputState(InputKey::KEY_D)) {
		inputVelocity += m_coreServiceLocator->getCameraSystem()->m_right;
	}
	glm::vec3 targetVelocity(m_movementComponent->getTargetVelocity());
	switch (m_movementComponent->getMovementMode()) {
		case MovementMode::STANDARD: {
			inputVelocity.y = 0.0f;
			if (glm::length(inputVelocity) > 0.0f) {
				inputVelocity = glm::normalize(inputVelocity);
			}
			targetVelocity.x = inputVelocity.x * m_movementComponent->getMovementSpeed();
			targetVelocity.z = inputVelocity.z * m_movementComponent->getMovementSpeed();

			if (inputManager->getInputStatePressed(InputKey::KEY_SPACE)) {
				if (m_movementComponent->getIsGrounded()) {
					glm::vec3 velocity(m_movementComponent->getVelocity());
					velocity.y = m_jumpForce;
					//m_movementComponent->m_velocity.z = -10000.0f;
					m_movementComponent->setVelocity(velocity);
				}
			}
			break;
		}
		case MovementMode::FLY: {
			inputVelocity.y = 0.0f;
			if (glm::length(inputVelocity) > 0.0f) {
				inputVelocity = glm::normalize(inputVelocity);
			}
			if (inputManager->getInputState(InputKey::KEY_SPACE)) {
				inputVelocity.y = 1.0f;
			}
			else if (inputManager->getInputState(InputKey::KEY_LEFT_SHIFT)) {
				inputVelocity.y = -1.0f;
			}
			
			targetVelocity.x = inputVelocity.x * m_movementComponent->getFlySpeed();
			targetVelocity.z = inputVelocity.z * m_movementComponent->getFlySpeed();
			targetVelocity.y = inputVelocity.y * m_movementComponent->getFlySpeed();
			
			break;
		}
		case MovementMode::FLYNOCLIP: {
			if (glm::length(inputVelocity) > 0.0f) {
				inputVelocity = glm::normalize(inputVelocity);
			}
			targetVelocity.x = inputVelocity.x * m_movementComponent->getFlySpeed();
			targetVelocity.y = inputVelocity.y * m_movementComponent->getFlySpeed();
			targetVelocity.z = inputVelocity.z * m_movementComponent->getFlySpeed();
			break;
		}
	}
	m_movementComponent->setTargetVelocity(targetVelocity);
	if (inputManager->getInputStatePressed(InputKey::KEY_1)) {
		inventory->setItemBarSelectedSlot(0);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_2)) {
		inventory->setItemBarSelectedSlot(1);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_3)) {
		inventory->setItemBarSelectedSlot(2);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_4)) {
		inventory->setItemBarSelectedSlot(3);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_5)) {
		inventory->setItemBarSelectedSlot(4);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_6)) {
		inventory->setItemBarSelectedSlot(5);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_7)) {
		inventory->setItemBarSelectedSlot(6);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_8)) {
		inventory->setItemBarSelectedSlot(7);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_9)) {
		inventory->setItemBarSelectedSlot(8);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_0)) {
		inventory->setItemBarSelectedSlot(9);
	}
	if (inputManager->getInputState(InputKey::KEY_LEFT_CTRL)) {
		m_movementComponent->setFlySpeed(30.0f);
	} else {
		m_movementComponent->setFlySpeed(15.0f);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_F)) {
		m_movementModeIndex++;
		if ((m_movementModeIndex % ((int)MovementMode::FLYNOCLIP + 1)) == 0) {
			m_movementModeIndex = 0;
		}
		m_coreServiceLocator->getMovementSystem()->setMovementMode(this, (MovementMode)m_movementModeIndex);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_E)) {
		m_isOpenInventory = true;
		m_coreServiceLocator->getInput()->setMouseCapture(false);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_ESC)) {
		m_coreServiceLocator->getApplicationManager()->requestCoreStateChange(CoreState::QUIT);
	}
}

void Player::processInventoryKeyInput() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	if (inputManager->getInputStatePressed(InputKey::KEY_E)) {
		m_isOpenInventory = false;
		m_coreServiceLocator->getInput()->setMouseCapture(true);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_ESC)) {
		m_coreServiceLocator->getApplicationManager()->requestCoreStateChange(CoreState::QUIT);
	}
}

Block* Player::getTargetBlock() {
	return m_targetBlock;
}

bool Player::getIsOpenInventory() {
	return m_isOpenInventory;
}


void Player::processMouseInput() {
	static bool leftMousePressed = false;
	static bool rightMousePressed = false;
	Inventory* inventory = m_coreServiceLocator->getInventory();
	InputManager* inputManager = m_coreServiceLocator->getInput();
	ItemHandle* selectedItem = inventory->getSelectedItem();
	if (inputManager->getInputState(InputMouseButton::MOUSE_LEFT)) {
		//BOOST_LOG_TRIVIAL(info) << "left mouse is pressed";
		selectedItem->itemPrimaryActionUpdate(m_coreServiceLocator);
	}
	else if(inputManager->getInputStateReleased(InputMouseButton::MOUSE_LEFT)) {
		//BOOST_LOG_TRIVIAL(info) << "left mouse was released";
		selectedItem->itemPrimaryActionEnd(m_coreServiceLocator);
	}
	if (inputManager->getInputState(InputMouseButton::MOUSE_RIGHT)) {
		selectedItem->itemSecondaryActionUpdate(m_coreServiceLocator);
	}
	else if (inputManager->getInputStateReleased(InputMouseButton::MOUSE_RIGHT)) {
		selectedItem->itemSecondaryActionEnd(m_coreServiceLocator);
	}
}

void Player::handleGameplayInput() {
	processMousePosition();
	processMouseScroll();
	processMouseInput();
	processKeyinput();
}

void Player::handleInventoryInput() {
	processInventoryKeyInput();
}

void Player::update() {
	if (!m_isOpenInventory) {
		handleGameplayInput();
	}
	else {
		handleInventoryInput();
	}
	m_coreServiceLocator->getCameraSystem()->setPlayerPosition(m_position);
	m_coreServiceLocator->getWorld()->updateGenerationOrigin(m_position);
	m_targetBlock = getFirstNonEmptyBlock();
	glm::vec3 coords = m_coreServiceLocator->getWorld()->getCubeAbsCoords(m_coreServiceLocator->getWorld()->getCubeByCoords(m_position));
	//BOOST_LOG_TRIVIAL(info) << "pos: " << m_position.x << " " << m_position.y << " " << m_position.z;
	//BOOST_LOG_TRIVIAL(info) << "coords: " << coords.x << " " << coords.y << " " << coords.z;
}

Block* Player::getFirstNonEmptyBlock() {
	Block* target = nullptr;
	std::vector<Block*> cubesInRay;
	glm::vec3 cameraPos = m_coreServiceLocator->getCameraSystem()->getCameraPosition();
	glm::vec3 cameraLookDir = m_coreServiceLocator->getCameraSystem()->m_front;
	//BOOST_LOG_TRIVIAL(info) << "player pos: " << m_position.x << " " << m_position.y << " " << m_position.z;
	//BOOST_LOG_TRIVIAL(info) << "player campos: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z;
	//BOOST_LOG_TRIVIAL(info) << "player front: " << cameraLookDir.x << " " << cameraLookDir.y << " " << cameraLookDir.z;
	m_coreServiceLocator->getWorld()->getCubesInRay(cameraPos, cameraLookDir, m_targetCubeRayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			glm::vec3 cubeCoords = m_coreServiceLocator->getWorld()->getCubeAbsCoords(cubesInRay.at(i));
			//BOOST_LOG_TRIVIAL(info) << "cube " << i << " coords: " << cubeCoords.x << " " << cubeCoords.y << " " << cubeCoords.z;
			if (cubesInRay.at(i)->getBlockId() != BlockId::AIR && cubesInRay.at(i)->getBlockId() != BlockId::NONE) {
				target = cubesInRay.at(i);
				//BOOST_LOG_TRIVIAL(info) << "target is cube " << i;
				break;
			}
		}
	}
	return target;
}

Block* Player::getLastEmptyBlock() {
	Block* target = nullptr;
	std::vector<Block*> cubesInRay;
	glm::vec3 cameraPos = m_coreServiceLocator->getCameraSystem()->getCameraPosition();
	glm::vec3 cameraLookDir = m_coreServiceLocator->getCameraSystem()->m_front;
	m_coreServiceLocator->getWorld()->getCubesInRay(cameraPos, cameraLookDir, m_targetCubeRayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			if (i > 0 && cubesInRay.at(i)->getBlockId() != BlockId::AIR && cubesInRay.at(i)->getBlockId() != BlockId::NONE) {
				target = cubesInRay.at(i - 1);
				break;
			}
		}
	}
	return target;
}