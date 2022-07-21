#include "BiomeService.h"

BiomeService::BiomeService(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_biomeManager(nullptr) {

}

void BiomeService::init(BiomeManager* biomeManager) {
	m_biomeManager = biomeManager;
}

void BiomeService::onNotify(Event& newEvent) {

}

unsigned int BiomeService::getBiomesCount() {
	return m_biomeManager->getBiomesCount();
}

TextureBuffer* BiomeService::getBiomeColorsBuffer() {
	return m_biomeManager->getBiomeColorsBuffer();
}

int BiomeService::getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	return m_biomeManager->getBiomeCubeColors(biomeId, cubeId, faceSide);
}

Biome** BiomeService::getBiomes() {
	return m_biomeManager->getBiomes();
}