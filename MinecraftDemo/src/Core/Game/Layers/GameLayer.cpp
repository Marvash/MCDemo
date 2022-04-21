#include "GameLayer.h"

GameLayer::GameLayer(CoreServiceLocator* coreServiceLocator) : 
	Layer("Game Layer"),
	m_gameServiceLocator(new GameServiceLocator()),
	m_coreServiceLocator(coreServiceLocator),
	m_atlas(nullptr),
	m_biomeManager(nullptr),
	m_chunkManager(nullptr),
	m_player(nullptr) {
}

void GameLayer::update() {
	m_player->update();

	m_chunkManager->updateGenerationOrigin(m_player->getCamera()->m_position, m_player->getCamera()->m_front);
	m_chunkManager->reloadChunks();
	m_chunkManager->submitRenderableChunks(m_coreServiceLocator->getRenderer());

	m_coreServiceLocator->getRenderer()->draw(m_player->getCamera());
}

void GameLayer::onNotify(Event& newEvent) {
	m_player->onNotify(newEvent);
}

void GameLayer::requestApplicationQuit() {
	m_coreServiceLocator->getApplicationManager()->requestCoreStateChange(CoreState::QUIT);
}

void GameLayer::onAdd() {
	m_atlas = new Atlas();
	m_gameServiceLocator->provide(m_atlas);
	m_biomeManager = new BiomeManager();
	m_gameServiceLocator->provide(m_biomeManager);
	m_chunkManager = new ChunkManager(m_gameServiceLocator, glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameServiceLocator->provide(m_chunkManager);

	m_coreServiceLocator->getRenderer()->setAtlas(m_atlas);
	m_coreServiceLocator->getRenderer()->setBiomeManager(m_biomeManager);
	
	m_chunkManager->startGeneratorThreads();
	m_chunkManager->startBuilderThreads();
	m_player = new Player(m_coreServiceLocator, m_gameServiceLocator);
}

void GameLayer::onRemove() {
	delete m_chunkManager;
	delete m_player;
	delete m_atlas;
	delete m_biomeManager;
}