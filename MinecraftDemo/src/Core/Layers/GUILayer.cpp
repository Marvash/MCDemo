#include "GUILayer.h"

GUILayer::GUILayer(CoreServiceLocator* coreServiceLocator) : 
	Layer("GUI Layer"), 
	m_coreServiceLocator(coreServiceLocator),
	m_debugPanel(nullptr) {

}

void GUILayer::onAdd() {
	m_debugPanel = new DebugPanel();
}

void GUILayer::onRemove() {
	delete m_debugPanel;
}

void GUILayer::update() {
	updateDebugPanel();
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_debugPanel);
}

void GUILayer::updateDebugPanel() {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	CameraSystem* cameraSystem = m_coreServiceLocator->getCameraSystem();
	if (player != nullptr) {
		m_debugPanel->setPlayerPosition(player->m_position);
		m_debugPanel->setPlayerLook(cameraSystem->m_front);
		m_debugPanel->setPlayerVelocity(player->m_movementComponent->m_velocity);
		std::string cubeName = Cube::getDisplayName(player->getSelectedCube());
		m_debugPanel->setSelectedCubeName(cubeName);
		cubeName = "None";
		if (player->getTargetCube() != nullptr) {
			cubeName = Cube::getDisplayName(player->getTargetCube()->getCubeId());
		}
		m_debugPanel->setTargetCubeName(cubeName);
	}
}

void GUILayer::onNotify(Event& newEvent) {

}