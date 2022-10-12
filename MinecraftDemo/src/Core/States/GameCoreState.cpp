#include "GameCoreState.h"
#include "Core/Core.h"

GameCoreState::GameCoreState(Core* core, CoreState id, std::string name) :
	ApplicationCoreState(core, id, name),
	m_gameLayer(nullptr),
	m_GUILayer(nullptr) {
}

void GameCoreState::enter() {
	BOOST_LOG_TRIVIAL(info) << "---GAME STATE ENTER---";
	m_gameLayer = new GameLayer(m_core->getServiceLocator());
	m_GUILayer = new GameGUILayer(m_core->getServiceLocator());
	m_layerStack->addLayer(m_gameLayer);
	m_layerStack->addOverlay(m_GUILayer);
}

void GameCoreState::exit() {
	BOOST_LOG_TRIVIAL(info) << "---GAME STATE EXIT---";
	m_layerStack->removeLayer(m_gameLayer);
	m_layerStack->removeOverlay(m_GUILayer);
	delete m_gameLayer;
	delete m_GUILayer;
}