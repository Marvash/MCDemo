#include "QuitCoreState.h"
#include "Core/Core.h"

QuitCoreState::QuitCoreState(Core* core, CoreState id, std::string name) :
	ApplicationCoreState(core, id, name) {

}

void QuitCoreState::enter() {
	BOOST_LOG_TRIVIAL(info) << "---QUIT STATE ENTER---";
	m_core->setApplicationExitFlag();
}

void QuitCoreState::exit() {
	BOOST_LOG_TRIVIAL(info) << "---QUIT STATE EXIT---";
}