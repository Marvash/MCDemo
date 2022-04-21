#include "GameCoreState.h"
#include "Core/Core.h"

GameCoreState::GameCoreState(Core* core, CoreState id, std::string name) :
	ApplicationCoreState(core, id, name) {
}

void GameCoreState::enter() {
	BOOST_LOG_TRIVIAL(info) << "---GAME STATE ENTER---";
	m_gameLayer = new GameLayer(m_core->getServiceLocator());
	m_layerStack->addLayer(m_gameLayer);
}

void GameCoreState::exit() {
	BOOST_LOG_TRIVIAL(info) << "---GAME STATE EXIT---";
	m_layerStack->removeLayer(m_gameLayer);
	delete m_gameLayer;
}