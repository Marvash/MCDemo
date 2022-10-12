#pragma once
#include "Core/Core.h"
#include "Core/States/ApplicationCoreState.h"
#include <string>

class Application {
public:
	Application(std::string appName);
	~Application();
	virtual void run() = 0;

protected:
	Core* core;
	std::vector<ApplicationCoreState*> applicationStates;
	std::string appName;
};