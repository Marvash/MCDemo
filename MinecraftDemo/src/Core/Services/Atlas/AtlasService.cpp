#include "AtlasService.h"

AtlasService::AtlasService(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_atlas(nullptr) {

}

void AtlasService::init(Atlas* atlas) {
	m_atlas = atlas;
}

void AtlasService::onNotify(Event& newEvent) {

}

int AtlasService::getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	return m_atlas->getAtlasTexIndex(cubeId, faceSide);
}

AtlasTexture* AtlasService::getAtlasTexture() {
	return m_atlas->getAtlasTexture();
}

TextureBuffer* AtlasService::getTexCoordsBuffer() {
	return m_atlas->getTexCoordsBuffer();
}

