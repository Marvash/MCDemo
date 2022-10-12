#pragma once
#include "Utils/StateMachine/State.h"
#include "Core/States/CoreStateEnum.h"
#include "Core/LayerStack.h"

class Core;

class ApplicationCoreState : public State<CoreState> {
public:
	ApplicationCoreState(Core* core, CoreState id, std::string name = "NoState");
	LayerStack* getLayerStack();
protected:
	Core* m_core;
	LayerStack* m_layerStack;
};