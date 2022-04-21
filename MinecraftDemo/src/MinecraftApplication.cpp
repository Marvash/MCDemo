#define STB_IMAGE_IMPLEMENTATION
#include "MinecraftApplication.h"

MinecraftApplication::MinecraftApplication() : Application("Minecraft Demo") {
	applicationStates.push_back(new InitCoreState(core, CoreState::INIT, "Init State"));
	applicationStates.push_back(new MainMenuCoreState(core, CoreState::MAIN_MENU, "Main Menu State"));
	applicationStates.push_back(new GameCoreState(core, CoreState::GAME, "Game State"));
	applicationStates.push_back(new QuitCoreState(core, CoreState::QUIT, "Quit State"));
}

MinecraftApplication::~MinecraftApplication() {
	
}

void MinecraftApplication::run() {
	for (auto& state : applicationStates) {
		core->addState(state);
	}
	core->setNextState(CoreState::INIT);
	core->run();
}

int main() {
	try {
		MinecraftApplication application;
		application.run();
	}
	catch (std::exception& e) {
		BOOST_LOG_TRIVIAL(fatal) << "ANOMALOUS BEHAVIOUR DETECTED: " << e.what();
	}
}