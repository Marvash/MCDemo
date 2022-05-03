#pragma once
#include "ApplicationCoreState.h"
#include "CoreStateEnum.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Layers/GameLayer.h"
#include "Core/Layers/GUILayer.h"
#include <boost/log/trivial.hpp>

class Core;

class GameCoreState : public ApplicationCoreState {
public:
	GameCoreState(Core* core, CoreState id, std::string name = "NoState");

	void enter() override;
	void exit() override;
	
private:
	GameLayer* m_gameLayer;
	GUILayer* m_GUILayer;
};