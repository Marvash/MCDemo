#pragma once
#include "Utils/StateMachine/StateMachine.h"
#include "Core/States/CoreStateEnum.h"
#include "Core/States/InitCoreState.h"
#include "Core/States/MainMenuCoreState.h"
#include "Core/States/GameCoreState.h"
#include "Core/States/QuitCoreState.h"
#include "Exceptions/Exception.h"
#include "Core/Services/CoreServiceLocator.h"
#include "CoreEventDispatcher.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Services/BiomeManager/BiomeManager.h"
#include "Core/Services/BiomeManager/BiomeService.h"
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/Atlas/AtlasService.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/MovementSystem/MovementSystem.h"
#include "Core/Services/World/World.h"
#include "Core/Services/Window/Window.h"
#include "Core/Services/Input/InputManager.h"
#include "Core/Services/CameraSystem/CameraSystem.h"
#include "LayerStack.h"
#include <Boost/log/trivial.hpp>

class Core
{
public:
	~Core();
	Core();

	void run();
	CoreServiceLocator* getServiceLocator();
	void addState(ApplicationCoreState* newState);
	void setNextState(CoreState nextStateId);
	void setApplicationExitFlag();

private:
	void setNextState(ApplicationCoreState* state);
	void initializeCoreServices();
	void shutdownCoreServices();
	void setCurrentLayerStack(LayerStack* layerStack);
	void transitionToNextState();
	void update(double& dt);

	bool m_stateChangeRequested;
	bool m_shouldExitApplication;
	ApplicationCoreState* m_nextState;
	StateMachine<CoreState>* m_coreSM;
	CoreServiceLocator* m_serviceLocator;
	CoreEventDispatcher* m_eventDispatcher;
	LayerStack* m_currentLayerStack;
	ChunkManager* m_chunkManager;
	BiomeManager* m_biomeManager;
	Atlas* m_atlas;
	Renderer* m_renderer;
};

