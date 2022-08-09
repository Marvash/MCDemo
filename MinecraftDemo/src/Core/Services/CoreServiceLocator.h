#pragma once
#include "Core/Services/Input/InputManager.h"
#include "Core/Services/Window/Window.h"
#include "Core/Services/Application/ApplicationManager.h"
#include "Core/Services/MovementSystem/MovementSystem.h"
#include "Core/Services/World/World.h"
#include "Core/Services/Graphics/Graphics.h"
#include "Core/Services/CameraSystem/CameraSystem.h"
#include "Core/Services/GameObjectManager/GameObjectManager.h"
#include "Core/Services/Atlas/AtlasService.h"
#include "Core/Services/BiomeManager/BiomeService.h"

class CoreServiceLocator {
public:
	CoreServiceLocator();

	InputManager* getInput();
	Window* getWindow();
	ApplicationManager* getApplicationManager();
	MovementSystem* getMovementSystem();
	World* getWorld();
	AtlasService* getAtlasService();
	Graphics* getGraphics();
	CameraSystem* getCameraSystem();
	GameObjectManager* getGameObjectManager();
	BiomeService* getBiomeService();

	void provide(InputManager* input);
	void provide(Window* window);
	void provide(ApplicationManager* applicationManager);
	void provide(MovementSystem* movementSystem);
	void provide(World* biomeManager);
	void provide(Graphics* biomeManager);
	void provide(CameraSystem* cameraSystem);
	void provide(GameObjectManager* gameObjectManager);
	void provide(AtlasService* atlasService);
	void provide(BiomeService* biomeService);

private:
	InputManager* m_input;
	Window* m_window;
	Graphics* m_graphics;
	ApplicationManager* m_applicationManager;
	MovementSystem* m_movementSystem;
	World* m_world;
	CameraSystem* m_cameraSystem;
	GameObjectManager* m_gameObjectManager;
	AtlasService* m_atlasService;
	BiomeService* m_biomeService;
};

