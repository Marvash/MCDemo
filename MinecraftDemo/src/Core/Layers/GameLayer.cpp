#include "GameLayer.h"

GameLayer::GameLayer(CoreServiceLocator* coreServiceLocator) :
	Layer("Game Layer"),
	m_coreServiceLocator(coreServiceLocator),
	m_player(nullptr) {
}

void GameLayer::update() {
	m_coreServiceLocator->getWorld()->reloadChunks();
	m_coreServiceLocator->getWorld()->updateRenderableChunks();
	m_coreServiceLocator->getGraphics()->submitRenderableChunks(m_coreServiceLocator->getWorld()->getRenderableChunks());
}

void GameLayer::onNotify(Event& newEvent) {
	m_player->onNotify(newEvent);
}

void GameLayer::onAdd() {
	m_player = new Player(m_coreServiceLocator);
	m_coreServiceLocator->getWorld()->updateGenerationOrigin(m_player->m_position);
	m_coreServiceLocator->getWorld()->startThreads();
	m_coreServiceLocator->getGraphics()->setCameraRenderingData(m_coreServiceLocator->getCameraSystem()->getCameraRenderingData());
}

void GameLayer::onRemove() {
	delete m_player;
}