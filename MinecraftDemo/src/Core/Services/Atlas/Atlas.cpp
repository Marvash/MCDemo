#include "Atlas.h"

#define ATLASMIP0 "assets/atlas0.png"
#define ATLASMIP1 "assets/atlas1.png"
#define ATLASMIP2 "assets/atlas2.png"
#define ATLASMIP3 "assets/atlas3.png"
#define ATLASMIP4 "assets/atlas4.png"

Atlas::Atlas(CoreEventDispatcher* coreEventDispatcher) : CoreService(coreEventDispatcher) {
}

Atlas::~Atlas() {
	delete m_texture;
	delete m_atlasTexCoords;
	delete m_texCoords;
}

AtlasTexture* Atlas::getAtlasTexture() {
	return m_texture;
}

TextureBuffer* Atlas::getTexCoordsBuffer() {
	return m_texCoords;
}

void Atlas::init() {
	std::vector<std::string> mipFilePaths;
	mipFilePaths.push_back(ATLASMIP0);
	mipFilePaths.push_back(ATLASMIP1);
	mipFilePaths.push_back(ATLASMIP2);
	mipFilePaths.push_back(ATLASMIP3);
	mipFilePaths.push_back(ATLASMIP4);
	m_texture = new AtlasTexture(mipFilePaths);
	m_atlasTexCoords = new AtlasTexCoordinates(m_texture->m_atlasWidth, m_texture->m_atlasHeight);
	m_texCoords = new TextureBuffer(m_atlasTexCoords->m_atlasTexCoordinates, m_atlasTexCoords->TEX_COORDINATES_SIZE);
}

void Atlas::onNotify(Event& newEvent) {

}

void Atlas::notify(Event& newEvent) {

}

int Atlas::getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	switch (cubeId) {
	case Cube::CubeId::GRASS_BLOCK:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 0;
		case Cube::FaceSide::TOP:
			return 24;
		case Cube::FaceSide::BOTTOM:
			return 48;
		}
		break;
	case Cube::CubeId::DIRT_BLOCK:
		return 72;
	case Cube::CubeId::STONE_BLOCK:
		return 96;
	case Cube::CubeId::SAND_BLOCK:
		return 120;
	case Cube::CubeId::SNOWY_GRASS_BLOCK:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 144;
		case Cube::FaceSide::TOP:
			return 168;
		case Cube::FaceSide::BOTTOM:
			return 192;
		}
		break;
	case Cube::CubeId::OAK_LOG_BLOCK:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 216;
		case Cube::FaceSide::TOP:
		case Cube::FaceSide::BOTTOM:
			return 240;
		}
		break;
	case Cube::CubeId::LEAVES_BLOCK:
		return 264;
		break;
	}
	BOOST_LOG_TRIVIAL(warning) << "Returning -1";
	return -1;
}