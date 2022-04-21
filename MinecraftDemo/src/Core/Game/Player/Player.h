#pragma once
#include "Core/Events/MouseButtonEvent.h"
#include "Core/Events/MouseMoveEvent.h"
#include "Core/Events/MouseScrollEvent.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Game/Camera/Camera.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Game/GameServiceLocator/GameServiceLocator.h"
#include "Core/Game/Cube/Cube.h"

class Player : public GameObject
{
public:
	Player(CoreServiceLocator* coreServiceLocator, GameServiceLocator* gameServiceLocator);
	void onNotify(Event& newEvent) override;
	void update();
	Camera* getCamera();
private:
	void handleMouseMoveEvent(MouseMoveEvent& mouseMoveEvent);
	void processKeyinput();
	void processMouseInput();
	void processMousePosition();
	void processMouseScroll();

	Camera* m_camera;
	CoreServiceLocator* m_coreServiceLocator;
	GameServiceLocator* m_gameServiceLocator;
	bool firstMouseMove;
	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;
	Cube::CubeId selectedCubeId;
};

