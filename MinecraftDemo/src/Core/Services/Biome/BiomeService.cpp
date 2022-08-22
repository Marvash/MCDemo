#include "BiomeService.h"

BiomeService::BiomeService(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_biomeLibrary(nullptr) {

}

void BiomeService::init(BiomeLibrary* biomeLibrary) {
	m_biomeLibrary = biomeLibrary;
}

void BiomeService::onNotify(Event& newEvent) {

}

unsigned int BiomeService::getBiomesCount() {
	return m_biomeLibrary->getBiomesCount();
}

TextureBuffer* BiomeService::getBiomeColorsBuffer() {
	return m_biomeLibrary->getBiomeColorsBuffer();
}

int BiomeService::getBiomeCubeColors(Biome::BiomeId biomeId, CubeId cubeId, Cube::FaceSide faceSide) {
	return m_biomeLibrary->getBiomeCubeColors(biomeId, cubeId, faceSide);
}

Biome** BiomeService::getBiomes() {
	return m_biomeLibrary->getBiomes();
}