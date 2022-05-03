#pragma once
#include "Core/Services/Input/InputManager.h"
#include "Core/Services/Window/Window.h"
#include "Core/Services/Application/ApplicationManager.h"
#include "Core/Services/MovementSystem/MovementSystem.h"
#include "Core/Services/World/World.h"
#include "Core/Services/Graphics/Graphics.h"
#include "Core/Services/CameraSystem/CameraSystem.h"

class CoreServiceLocator {
public:
	CoreServiceLocator();

	InputManager* getInput();
	Window* getWindow();
	ApplicationManager* getApplicationManager();
	MovementSystem* getMovementSystem();
	World* getWorld();
	Graphics* getGraphics();
	CameraSystem* getCameraSystem();

	void provide(InputManager* input);
	void provide(Window* window);
	void provide(ApplicationManager* applicationManager);
	void provide(MovementSystem* movementSystem);
	void provide(World* biomeManager);
	void provide(Graphics* biomeManager);
	void provide(CameraSystem* cameraSystem);

private:
	InputManager* m_input;
	Window* m_window;
	Graphics* m_graphics;
	ApplicationManager* m_applicationManager;
	MovementSystem* m_movementSystem;
	World* m_world;
	CameraSystem* m_cameraSystem;
};

