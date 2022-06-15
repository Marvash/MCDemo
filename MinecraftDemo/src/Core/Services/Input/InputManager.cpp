#include "InputManager.h"

std::vector<Event*> InputManager::inputEventsList;
std::map<InputKey, InputAction> InputManager::m_inputKeyMap;
std::map<InputMouseButton, InputAction> InputManager::m_inputMouseMap;
std::map<InputKey, InputAction> InputManager::m_previousInputKeyMap;
std::map<InputMouseButton, InputAction> InputManager::m_previousInputMouseMap;
double InputManager::mouseXPos = 0.0;
double InputManager::mouseYPos = 0.0;
double InputManager::mouseLastXPos = 0.0;
double InputManager::mouseLastYPos = 0.0;
double InputManager::scrollXOffset = 0.0;
double InputManager::scrollYOffset = 0.0;


InputManager::InputManager(CoreEventDispatcher* eventDispatcher) : CoreService(eventDispatcher), window(nullptr) {
	for (int i = 0; i <= (int)InputMouseButton::MOUSE_RIGHT; i++) {
		m_inputMouseMap[(InputMouseButton)i] = InputAction::RELEASE;
		m_previousInputMouseMap[(InputMouseButton)i] = m_inputMouseMap[(InputMouseButton)i];
	}
	for (int i = 0; i <= (int)InputKey::KEY_ESC; i++) {
		m_inputKeyMap[(InputKey)i] = InputAction::RELEASE;
		m_previousInputKeyMap[(InputKey)i] = m_inputKeyMap[(InputKey)i];
	}
}

void InputManager::onNotify(Event& newEvent) {
	switch (newEvent.getEventType()) {
	case EventType::WINDOW_INIT:
		WindowInitEvent* windowInitEvent = static_cast<WindowInitEvent*>(&newEvent);
		window = windowInitEvent->m_window;
		setupGlfwCallbacks(window);
		break;
	}
}

void InputManager::setupGlfwCallbacks(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)&InputManager::framebufferSizeCallback);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)&InputManager::mousePosCallback);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)&InputManager::mouseButtonCallback);
	glfwSetScrollCallback(window, (GLFWscrollfun)&InputManager::scrollCallback);
	glfwSetKeyCallback(window, (GLFWkeyfun)&InputManager::keyCallback);
}

void InputManager::addEventToQueue(Event* newEvent) {
	inputEventsList.push_back(newEvent);
}

void InputManager::clearEventQueue() {
	for (Event* e : inputEventsList) {
		delete e;
	}
	inputEventsList.clear();
}

bool InputManager::getInputState(InputMouseButton button) {
	return m_inputMouseMap[button] == InputAction::PRESS;
}

bool InputManager::getInputState(InputKey key) {
	return m_inputKeyMap[key] == InputAction::PRESS;
}

bool InputManager::getInputStatePressed(InputMouseButton button) {
	return m_previousInputMouseMap[button] == InputAction::RELEASE && m_inputMouseMap[button] == InputAction::PRESS;
}

bool InputManager::getInputStatePressed(InputKey key) {
	return m_previousInputKeyMap[key] == InputAction::RELEASE && m_inputKeyMap[key] == InputAction::PRESS;
}

double InputManager::getMouseXDelta() {
	return mouseXPos - mouseLastXPos;
}

double InputManager::getMouseYDelta() {
	// reversed since y-coordinates go from bottom to top
	return mouseLastYPos - mouseYPos;
}

double InputManager::getScrollXDelta() {
	return scrollXOffset;
}

double InputManager::getScrollYDelta() {
	return scrollYOffset;
}

void InputManager::resetPressedInputMaps() {
	for (auto& pair : m_previousInputMouseMap) {
		pair.second = m_inputMouseMap[pair.first];
	}
	for (auto& pair : m_previousInputKeyMap) {
		pair.second = m_inputKeyMap[pair.first];
	}
}

void InputManager::updateLastMousePos() {
	mouseLastXPos = mouseXPos;
	mouseLastYPos = mouseYPos;
}

void InputManager::resetScrollInput() {
	scrollXOffset = 0.0;
	scrollYOffset = 0.0;
}

void InputManager::resetInputManager() {
	clearEventQueue();
	resetPressedInputMaps();
	updateLastMousePos();
	resetScrollInput();
}

InputMouseButton InputManager::glfwMouseButtonToInputMouseButton(int button) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		return InputMouseButton::MOUSE_LEFT;
	case GLFW_MOUSE_BUTTON_RIGHT:
		return InputMouseButton::MOUSE_RIGHT;
	}
	return InputMouseButton::UNKNOWN;
}

InputKey InputManager::glfwKeyToInputKey(int key) {
	switch (key) {
	case GLFW_KEY_W:
		return InputKey::KEY_W;
	case GLFW_KEY_A:
		return InputKey::KEY_A;
	case GLFW_KEY_S:
		return InputKey::KEY_S;
	case GLFW_KEY_D:
		return InputKey::KEY_D;
	case GLFW_KEY_F:
		return InputKey::KEY_F;
	case GLFW_KEY_0:
		return InputKey::KEY_0;
	case GLFW_KEY_1:
		return InputKey::KEY_1;
	case GLFW_KEY_2:
		return InputKey::KEY_2;
	case GLFW_KEY_3:
		return InputKey::KEY_3;
	case GLFW_KEY_4:
		return InputKey::KEY_4;
	case GLFW_KEY_5:
		return InputKey::KEY_5;
	case GLFW_KEY_6:
		return InputKey::KEY_6;
	case GLFW_KEY_7:
		return InputKey::KEY_7;
	case GLFW_KEY_8:
		return InputKey::KEY_8;
	case GLFW_KEY_9:
		return InputKey::KEY_9;
	case GLFW_KEY_LEFT_CONTROL:
		return InputKey::KEY_LEFT_CTRL;
	case GLFW_KEY_ESCAPE:
		return InputKey::KEY_ESC;
	case GLFW_KEY_SPACE:
		return InputKey::KEY_SPACE;
	case GLFW_KEY_LEFT_SHIFT:
		return InputKey::KEY_LEFT_SHIFT;
	}
	return InputKey::UNKNOWN;
}

InputAction InputManager::glfwActionToInputAction(int action) {
	switch (action) {
	case GLFW_PRESS:
		return InputAction::PRESS;
	case GLFW_RELEASE:
		return InputAction::RELEASE;
	case GLFW_REPEAT:
		return InputAction::PRESS;
		//return InputAction::REPEAT;
	}
	return InputAction::UNKNOWN;
}

void InputManager::dispatchInputEvents() {
	for (Event* e : inputEventsList) {
		m_eventDispatcher->notify(*e);
	}
}

void InputManager::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	WindowResizeEvent* newEvent = new WindowResizeEvent(width, height);
	addEventToQueue(newEvent);
}

void InputManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	static bool firstMouseInput = true;
	if (firstMouseInput) {
		mouseLastXPos = xpos;
		mouseLastYPos = ypos;
		firstMouseInput = false;
	}
	mouseXPos = xpos;
	mouseYPos = ypos;
	MouseMoveEvent* newEvent = new MouseMoveEvent(xpos, ypos);
	addEventToQueue(newEvent);
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollXOffset = xoffset;
	scrollYOffset = yoffset;
	MouseScrollEvent* newEvent = new MouseScrollEvent(xoffset, yoffset);
	addEventToQueue(newEvent);
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (m_inputMouseMap[glfwMouseButtonToInputMouseButton(button)] != glfwActionToInputAction(action)) {
		m_inputMouseMap[glfwMouseButtonToInputMouseButton(button)] = glfwActionToInputAction(action);
		MouseButtonEvent* newEvent = new MouseButtonEvent(glfwMouseButtonToInputMouseButton(button), glfwActionToInputAction(action));
		addEventToQueue(newEvent);
	}
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (m_inputKeyMap[glfwKeyToInputKey(key)] != glfwActionToInputAction(action)) {
		m_inputKeyMap[glfwKeyToInputKey(key)] = glfwActionToInputAction(action);
		KeyEvent* newEvent = new KeyEvent(glfwKeyToInputKey(key), glfwActionToInputAction(action));
		addEventToQueue(newEvent);
	}
}