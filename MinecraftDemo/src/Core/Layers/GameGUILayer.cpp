#include "GameGUILayer.h"

GameGUILayer::GameGUILayer(CoreServiceLocator* coreServiceLocator) :
	Layer("GUI Layer"), 
	m_coreServiceLocator(coreServiceLocator),
	m_debugPanel(nullptr),
	m_itemBar(nullptr),
	m_inventory(nullptr),
	m_iconManager(nullptr) {

}

void GameGUILayer::onAdd() {
	m_debugPanel = new DebugPanel(m_coreServiceLocator);
	m_crosshair = new Crosshair(m_coreServiceLocator);
	m_iconManager = new IconManager(m_coreServiceLocator);
	m_itemBar = new ItemBar(m_coreServiceLocator, m_iconManager);
	m_inventory = new Inventory(m_coreServiceLocator, m_iconManager);
}

void GameGUILayer::onRemove() {
	delete m_debugPanel;
	delete m_crosshair;
	delete m_itemBar;
	delete m_inventory;
}

void GameGUILayer::update() {
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_debugPanel);
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_crosshair);
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_itemBar);
	m_coreServiceLocator->getGraphics()->submitGUIElement(m_inventory);
}

void GameGUILayer::onNotify(Event& newEvent) {

}