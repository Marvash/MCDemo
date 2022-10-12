#pragma once
#include "ApplicationCoreState.h"
#include "CoreStateEnum.h"
#include <boost/log/trivial.hpp>

class Core;

class MainMenuCoreState : public ApplicationCoreState {
public:
	MainMenuCoreState(Core* core, CoreState id, std::string name = "NoState");

	void enter() override;
	void exit() override;
};