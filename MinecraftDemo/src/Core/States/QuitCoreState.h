#pragma once
#include "ApplicationCoreState.h"
#include "CoreStateEnum.h"
#include <boost/log/trivial.hpp>

class Core;

class QuitCoreState : public ApplicationCoreState {
public:
	QuitCoreState(Core* core, CoreState id, std::string name = "NoState");

	void enter() override;
	void exit() override;
};

