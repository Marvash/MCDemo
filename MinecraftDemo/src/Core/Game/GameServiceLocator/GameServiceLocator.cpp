#include "GameServiceLocator.h"

GameServiceLocator::GameServiceLocator() {

}

Atlas* GameServiceLocator::getAtlas() {
	return m_atlas;
}

BiomeManager* GameServiceLocator::getBiomeManager() {
	return m_biomeManager;
}

ChunkManager* GameServiceLocator::getChunkManager() {
	return m_chunkManager;
}

void GameServiceLocator::provide(Atlas* atlas) {
	m_atlas = atlas;
}

void GameServiceLocator::provide(BiomeManager* biomeManager) {
	m_biomeManager = biomeManager;
}

void GameServiceLocator::provide(ChunkManager* chunkManager) {
	m_chunkManager = chunkManager;
}