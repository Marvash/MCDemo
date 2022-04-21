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
};

