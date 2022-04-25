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
	m_debugPanel->setDeltaTime(m_coreServiceLocator->getApplicationManager()->getDeltaTime());
	m_coreServiceLocator->getRenderer()->submitGUIElement(m_debugPanel);
}

void GUILayer::onNotify(Event& newEvent) {

}