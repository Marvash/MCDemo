#include "GameLayer.h"

GameLayer::GameLayer(CoreServiceLocator* coreServiceLocator) :
	Layer("Game Layer"),
	m_coreServiceLocator(coreServiceLocator),
	m_player(nullptr) {
}

void GameLayer::update() {
	m_coreServiceLocator->getWorld()->reloadChunks();
}

void GameLayer::onNotify(Event& newEvent) {
	m_player->onNotify(newEvent);
}

void GameLayer::onAdd() {
	m_player = new Player(m_coreServiceLocator);
	m_coreServiceLocator->getWorld()->startThreads();
	m_coreServiceLocator->getGraphics()->setCameraRenderingData(m_coreServiceLocator->getCameraSystem()->getCameraRenderingData());
	for (RenderingComponent* component : *m_coreServiceLocator->getWorld()->getChunkComponents()) {
		m_coreServiceLocator->getGraphics()->registerComponent(component);
	}
}

void GameLayer::onRemove() {
	delete m_player;
}