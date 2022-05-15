#include "Player.h"
#include "Core/Services/CoreServiceLocator.h"

Player::Player(CoreServiceLocator* coreServiceLocator) : GameObject(coreServiceLocator, GameObjectType::DYNAMIC),
	m_selectedCubeId(Cube::CubeId::DIRT_BLOCK),
	m_jumpForce(8.2f),
	m_targetCube(nullptr),
	m_targetCubeRayLength(10.0f) {
	setMovementComponent(new MovementComponent());
	m_position = glm::vec3(112.0f, 2.0f, -44.0f);
	//m_position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_movementComponent->m_movementSpeed = 5.0f;
	m_movementComponent->m_fallingMovementSpeed = 3.0f;
	m_movementComponent->m_flySpeed = 15.0f;
	m_movementComponent->m_movementMode = MovementMode::DEFAULT;
	m_movementComponent->m_jumpStrength = 8.2f;
	m_coreServiceLocator->getCameraSystem()->setPlayerPosition(m_position);
	registerComponents();
	m_coreServiceLocator->getGameObjectManager()->setPlayerId(m_id);
}

void Player::onNotify(Event& newEvent) {
}

void Player::processMousePosition() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float xoffset = (float)inputManager->getMouseXDelta();
	float yoffset = (float)inputManager->getMouseYDelta();
	m_coreServiceLocator->getCameraSystem()->processMouseMovement(xoffset, yoffset, true);
}

void Player::processMouseScroll() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float yoffset = (float)inputManager->getScrollYDelta();
	m_coreServiceLocator->getCameraSystem()->processMouseScroll(yoffset);
}

void Player::processKeyinput() {
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
	if (m_movementComponent->m_movementMode == MovementMode::DEFAULT) {
		inputVelocity.y = 0.0f;
		if (glm::length(inputVelocity) > 0.0f) {
			inputVelocity = glm::normalize(inputVelocity);
		}
		m_movementComponent->m_velocity.x = inputVelocity.x;
		m_movementComponent->m_velocity.z = inputVelocity.z;

		if (inputManager->getInputStatePressed(InputKey::KEY_SPACE)) {
			if (m_movementComponent->m_isGrounded) {
				m_coreServiceLocator->getMovementSystem()->applyImpulse(m_movementComponent, glm::vec3(0.0f, m_jumpForce, 0.0f));
			}
		}
	}
	else {
		if (glm::length(inputVelocity) > 0.0f) {
			inputVelocity = glm::normalize(inputVelocity);
			m_movementComponent->m_velocity.x = inputVelocity.x;
			m_movementComponent->m_velocity.y = inputVelocity.y;
			m_movementComponent->m_velocity.z = inputVelocity.z;
		}
	}
	std::stringstream ss;
	if (inputManager->getInputStatePressed(InputKey::KEY_1)) {
		m_selectedCubeId = Cube::CubeId::SAND_BLOCK;
		std::string cubeId(std::to_string((int)m_selectedCubeId));
		std::string displayName(Cube::getDisplayName(Cube::CubeId::SAND_BLOCK));
		ss << cubeId << " " << displayName;
		std::string finalString(ss.str());
		PlayerSelectedCubeChange selectedCubeChange(finalString);
		m_coreServiceLocator->getGameObjectManager()->sendEvent(selectedCubeChange);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_2)) {
		m_selectedCubeId = Cube::CubeId::DIRT_BLOCK;
		std::string cubeId(std::to_string((int)m_selectedCubeId));
		std::string displayName(Cube::getDisplayName(Cube::CubeId::DIRT_BLOCK));
		ss << cubeId << " " << displayName;
		std::string finalString(ss.str());
		PlayerSelectedCubeChange selectedCubeChange(finalString);
		m_coreServiceLocator->getGameObjectManager()->sendEvent(selectedCubeChange);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_3)) {
		m_selectedCubeId = Cube::CubeId::STONE_BLOCK;
		std::string cubeId(std::to_string((int)m_selectedCubeId));
		std::string displayName(Cube::getDisplayName(Cube::CubeId::STONE_BLOCK));
		ss << cubeId << " " << displayName;
		std::string finalString(ss.str());
		PlayerSelectedCubeChange selectedCubeChange(finalString);
		m_coreServiceLocator->getGameObjectManager()->sendEvent(selectedCubeChange);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_4)) {
		m_selectedCubeId = Cube::CubeId::OAK_LOG_BLOCK;
		std::string cubeId(std::to_string((int)m_selectedCubeId));
		std::string displayName(Cube::getDisplayName(Cube::CubeId::OAK_LOG_BLOCK));
		ss << cubeId << " " << displayName;
		std::string finalString(ss.str());
		PlayerSelectedCubeChange selectedCubeChange(finalString);
		m_coreServiceLocator->getGameObjectManager()->sendEvent(selectedCubeChange);
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_5)) {
		m_selectedCubeId = Cube::CubeId::LEAVES_BLOCK;
		std::string cubeId(std::to_string((int)m_selectedCubeId));
		std::string displayName(Cube::getDisplayName(Cube::CubeId::LEAVES_BLOCK));
		ss << cubeId << " " << displayName;
		std::string finalString(ss.str());
		PlayerSelectedCubeChange selectedCubeChange(finalString);
		m_coreServiceLocator->getGameObjectManager()->sendEvent(selectedCubeChange);
	}
	if (inputManager->getInputState(InputKey::KEY_LEFT_CTRL)) {
		m_movementComponent->m_flySpeed = 30.0f;
	} else {
		m_movementComponent->m_flySpeed = 15.0f;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_F)) {
		if (m_movementComponent->m_movementMode == MovementMode::FLYNOCLIP) {
			m_movementComponent->m_movementMode = MovementMode::DEFAULT;
		}
		else {
			m_movementComponent->m_movementMode = MovementMode::FLYNOCLIP;
		}
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_ESC)) {
		m_coreServiceLocator->getApplicationManager()->requestCoreStateChange(CoreState::QUIT);
	}
}

Cube::CubeId Player::getSelectedCube() {
	return m_selectedCubeId;
}

Cube* Player::getTargetCube() {
	return m_targetCube;
}

void Player::processMouseInput() {
	static bool leftMousePressed = false;
	static bool rightMousePressed = false;
	InputManager* inputManager = m_coreServiceLocator->getInput();
	if (inputManager->getInputStatePressed(InputMouseButton::MOUSE_LEFT)) {
		m_coreServiceLocator->getWorld()->destroyBlock(m_targetCube);
	}
	if (inputManager->getInputStatePressed(InputMouseButton::MOUSE_RIGHT)) {                                        
		m_coreServiceLocator->getWorld()->placeBlock(getLastPlaceableCube(), m_selectedCubeId);
	}
}

void Player::update() {
	processMousePosition();
	processMouseScroll();
	processMouseInput();
	processKeyinput();
	m_coreServiceLocator->getCameraSystem()->setPlayerPosition(m_position);
	m_targetCube = getFirstSolidCube();
}

Cube* Player::getFirstSolidCube() {
	Cube* target = nullptr;
	std::vector<Cube*> cubesInRay;
	glm::vec3 cameraPos = m_coreServiceLocator->getCameraSystem()->getCameraPosition();
	glm::vec3 cameraLookDir = m_coreServiceLocator->getCameraSystem()->m_front;
	m_coreServiceLocator->getWorld()->getCubesInRay(cameraPos, cameraLookDir, m_targetCubeRayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			if (cubesInRay.at(i)->getCubeId() != Cube::CubeId::AIR_BLOCK && cubesInRay.at(i)->getCubeId() != Cube::CubeId::UNGENERATED_BLOCK) {
				target = cubesInRay.at(i);
				break;
			}
		}
	}
	return target;
}

Cube* Player::getLastPlaceableCube() {
	Cube* target = nullptr;
	std::vector<Cube*> cubesInRay;
	glm::vec3 cameraPos = m_coreServiceLocator->getCameraSystem()->getCameraPosition();
	glm::vec3 cameraLookDir = m_coreServiceLocator->getCameraSystem()->m_front;
	m_coreServiceLocator->getWorld()->getCubesInRay(cameraPos, cameraLookDir, m_targetCubeRayLength, cubesInRay);
	if (cubesInRay.size() > 0) {
		for (int i = 0; i < cubesInRay.size(); i++) {
			if (i > 0 && cubesInRay.at(i)->getCubeId() != Cube::CubeId::AIR_BLOCK && cubesInRay.at(i)->getCubeId() != Cube::CubeId::UNGENERATED_BLOCK) {
				target = cubesInRay.at(i - 1);
				break;
			}
		}
	}
	return target;
}