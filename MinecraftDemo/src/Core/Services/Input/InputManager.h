#pragma once
#include "Core/CoreEventDispatcher.h"
#include "Core/Services/CoreService.h"
#include "Core/Events/Event.h"
#include "Core/Events/WindowResizeEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/WindowInitEvent.h"
#include "InputEnums.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <boost/log/trivial.hpp>

class InputManager : public CoreService
{

public:
	InputManager(CoreEventDispatcher* eventDispatcher);

	bool getInputState(InputMouseButton button);
	bool getInputState(InputKey key);
	bool getInputStatePressed(InputMouseButton button);
	bool getInputStatePressed(InputKey key);
	double getMouseXDelta();
	double getMouseYDelta();
	double getScrollXDelta();
	double getScrollYDelta();
	void dispatchInputEvents();
	void resetInputManager();
	void setMouseCapture(bool capture);
	
	void onNotify(Event& newEvent) override;
private:
	GLFWwindow* window;

	static void addEventToQueue(Event* event);

	void setupGlfwCallbacks(GLFWwindow* window);
	void clearEventQueue();
	void resetPressedInputMaps();
	void updateLastMousePos();
	void resetScrollInput();
	static InputMouseButton glfwMouseButtonToInputMouseButton(int button);
	static InputKey glfwKeyToInputKey(int key);
	static InputAction glfwActionToInputAction(int action);
	//int inputButtonToGlfwButton(InputMouseButton button);
	//int inputKeyToGlfwKey(InputKey key);
	//int inputActionToGlfwAction(InputAction action);

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	static std::vector<Event*> inputEventsList;
	static std::map<InputKey, InputAction> m_inputKeyMap;
	static std::map<InputMouseButton, InputAction> m_inputMouseMap;
	static std::map<InputKey, InputAction> m_previousInputKeyMap;
	static std::map<InputMouseButton, InputAction> m_previousInputMouseMap;
	static double mouseXPos, mouseYPos;
	static double mouseLastXPos, mouseLastYPos;
	static double mouseXOffset, mouseYOffset;
	static double scrollXOffset, scrollYOffset;
	static bool firstMouseInput;

	bool m_isCapturingMouse;
};

