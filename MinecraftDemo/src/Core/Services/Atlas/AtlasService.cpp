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

int AtlasService::getCubeTexIndex(BlockId blockId, BlockFace faceSide) {
	return m_atlas->getCubeTexIndex(blockId, faceSide);
}

TextureBuffer* AtlasService::getTexCoordsBuffer() {
	return m_atlas->getTexCoordsBuffer();
}

