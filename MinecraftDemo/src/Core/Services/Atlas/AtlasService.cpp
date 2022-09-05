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

int AtlasService::getCubeTexIndex(CubeId cubeId, Cube::FaceSide faceSide) {
	return m_atlas->getCubeTexIndex(cubeId, faceSide);
}

AtlasTexture* AtlasService::getAtlasTexture() {
	return m_atlas->getAtlasTexture();
}

TextureBuffer* AtlasService::getTexCoordsBuffer() {
	return m_atlas->getTexCoordsBuffer();
}

