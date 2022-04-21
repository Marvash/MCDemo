#pragma once
#include "Core/Services/Input/InputManager.h"
#include "Core/Services/Window/Window.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/Application/ApplicationManager.h"

class CoreServiceLocator
{
public:
	CoreServiceLocator();

	InputManager* getInput();
	Window* getWindow();
	Renderer* getRenderer();
	ApplicationManager* getApplicationManager();

	void provide(InputManager* input);
	void provide(Window* window);
	void provide(Renderer* renderer);
	void provide(ApplicationManager* applicationManager);
private:
	InputManager* m_input;
	Window* m_window;
	Renderer* m_renderer;
	ApplicationManager* m_applicationManager;
};

