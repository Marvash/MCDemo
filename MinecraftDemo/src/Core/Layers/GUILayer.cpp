#include "GUILayer.h"

GUILayer::GUILayer(CoreServiceLocator* coreServiceLocator) : 
	Layer("GUI Layer"), 
	m_coreServiceLocator(coreServiceLocator),
	m_debugPanel(nullptr) {

}

void GUILayer::onAdd() {
	m_debugPanel = new DebugPanel();
	m_crosshair = new Crosshair(m_coreServiceLocator);
}

void GUILayer::onRemove() {
	delete m_debugPanel;
	delete m_crosshair;
}

void GUILayer::update() {
	updateDebugPanel();
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_debugPanel);
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_crosshair);
}

void GUILayer::updateDebugPanel() {
	Player* player = m_coreServiceLocator->getGameObjectManager()->getPlayer();
	CameraSystem* cameraSystem = m_coreServiceLocator->getCameraSystem();
	if (player != nullptr) {
		m_debugPanel->setPlayerPosition(player->m_position);
		m_debugPanel->setPlayerLook(cameraSystem->m_front);
		m_debugPanel->setPlayerVelocity(player->m_movementComponent->getVelocity());
		std::string cubeName = Cube::getDisplayName(player->getSelectedCube());
		m_debugPanel->setSelectedCubeName(cubeName);
		cubeName = "None";
		if (player->getTargetCube() != nullptr) {
			cubeName = Cube::getDisplayName(player->getTargetCube()->getCubeId());
		}
		m_debugPanel->setTargetCubeName(cubeName);
		std::string movementModeName = m_coreServiceLocator->getMovementSystem()->getMovementModeDisplayName(player->m_movementComponent->getMovementMode());
		m_debugPanel->setSelectedMovementModeName(movementModeName);
	}
}

void GUILayer::onNotify(Event& newEvent) {

}