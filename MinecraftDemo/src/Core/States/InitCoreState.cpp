#include "InitCoreState.h"
#include "Core/Core.h"

InitCoreState::InitCoreState(Core* core, CoreState id, std::string name) : 
	ApplicationCoreState(core, id, name) {

}

void InitCoreState::enter() {
    BOOST_LOG_TRIVIAL(info) << "---INIT STATE ENTER---";
	m_core->setNextState(CoreState::GAME);
}

void InitCoreState::exit() {
	BOOST_LOG_TRIVIAL(info) << "---INIT STATE EXIT---";
}