#include "Player.h"

Player::Player(CoreServiceLocator* coreServiceLocator, GameServiceLocator* gameServiceLocator) : GameObject(),
m_coreServiceLocator(coreServiceLocator),
	m_gameServiceLocator(gameServiceLocator),
	firstMouseMove(true),
	selectedCubeId(Cube::CubeId::DIRT_BLOCK) {
	m_camera = new Camera(glm::vec3(0.0f, 2.0f, 3.0f));
	m_position = glm::vec3(0.0f, 2.0f, 3.0f);
}

void Player::onNotify(Event& newEvent) {
	switch (newEvent.getEventType()) {
		case EventType::MOUSE_MOVE: {
			MouseMoveEvent* mouseMoveEvent = static_cast<MouseMoveEvent*>(&newEvent);
			handleMouseMoveEvent(*mouseMoveEvent);
			break;
		}
	}
}

void Player::handleMouseMoveEvent(MouseMoveEvent& mouseMoveEvent) {
	float xpos = (float)mouseMoveEvent.m_posX;
	float ypos = (float)mouseMoveEvent.m_posY;
	if (firstMouseMove) {
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstMouseMove = false;
	}
	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

	lastMouseX = xpos;
	lastMouseY = ypos;
	
}

void Player::processMousePosition() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float xoffset = (float)inputManager->getMouseXDelta();
	float yoffset = (float)inputManager->getMouseYDelta();
	m_camera->processMouseMovement(xoffset, yoffset, true);
}

void Player::processMouseScroll() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	float yoffset = (float)inputManager->getScrollYDelta();
	m_camera->processMouseScroll(yoffset);
}

void Player::processKeyinput() {
	InputManager* inputManager = m_coreServiceLocator->getInput();
	double dt = m_coreServiceLocator->getApplicationManager()->getDeltaTime();
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
	if (inputManager->getInputStatePressed(InputKey::KEY_1)) {
		selectedCubeId = Cube::CubeId::SAND_BLOCK;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_2)) {
		selectedCubeId = Cube::CubeId::DIRT_BLOCK;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_3)) {
		selectedCubeId = Cube::CubeId::STONE_BLOCK;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_4)) {
		selectedCubeId = Cube::CubeId::OAK_LOG;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_5)) {
		selectedCubeId = Cube::CubeId::LEAVES;
	}
	if (inputManager->getInputState(InputKey::KEY_LEFT_CTRL)) {
		m_camera->m_movementSpeed = 30.0f;
	} else {
		m_camera->m_movementSpeed = 15.0f;
	}
	if (inputManager->getInputStatePressed(InputKey::KEY_ESC)) {
		m_coreServiceLocator->getApplicationManager()->requestCoreStateChange(CoreState::QUIT);
	}
}

void Player::processMouseInput() {
	static bool leftMousePressed = false;
	static bool rightMousePressed = false;
	InputManager* inputManager = m_coreServiceLocator->getInput();
	if (inputManager->getInputStatePressed(InputMouseButton::MOUSE_LEFT)) {
		m_gameServiceLocator->getChunkManager()->destroyBlock();
	}
	if (inputManager->getInputStatePressed(InputMouseButton::MOUSE_RIGHT)) {
		m_gameServiceLocator->getChunkManager()->placeBlock(selectedCubeId);
	}
}

void Player::update() {
	processMousePosition();
	processMouseScroll();
	processMouseInput();
	processKeyinput();
}

Camera* Player::getCamera() {
	return m_camera;
}