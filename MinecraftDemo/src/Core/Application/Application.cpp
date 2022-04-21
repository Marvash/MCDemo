#include "Application.h"

Application::Application(std::string appName) : appName(appName) {
	core = new Core();
}

Application::~Application() {
	for (auto& state : applicationStates) {
		delete state;
	}
	delete core;
}