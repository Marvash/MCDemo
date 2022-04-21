#include <Core/States/MainMenuCoreState.h>
#include "Core/Core.h"

MainMenuCoreState::MainMenuCoreState(Core* core, CoreState id, std::string name) :
	ApplicationCoreState(core, id, name) {

}

void MainMenuCoreState::enter() {
	BOOST_LOG_TRIVIAL(info) << "---MAIN MENU STATE ENTER---";
}

void MainMenuCoreState::exit() {
	BOOST_LOG_TRIVIAL(info) << "---MAIN MENU STATE EXIT---";
}