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

TextureBuffer* Atlas::getTexCoordsBuffer() {
	return m_texCoords;
}

TextureBuffer* Atlas::getSecondaryTexCoordsBuffer() {
	return m_secondaryTexCoords;
}

AtlasTexture* Atlas::getAtlasTexture() {
	return m_texture;
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
	m_secondaryTexCoords = new TextureBuffer(m_atlasTexCoords->m_atlasSecondaryTexCoordinates, m_atlasTexCoords->SECONDARY_TEX_COORDINATES_SIZE);
}

void Atlas::onNotify(Event& newEvent) {

}

void Atlas::notify(Event& newEvent) {

}

int Atlas::getBlockSecondaryTexIndex(BlockBreakingContext::BlockBreakStage stage) {
	switch (stage) {
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS0:
			return -1;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS1:
			return 0;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS2:
			return 8;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS3:
			return 16;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS4:
			return 24;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS5:
			return 32;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS6:
			return 40;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS7:
			return 48;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS8:
			return 56;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS9:
			return 64;
		case BlockBreakingContext::BlockBreakStage::BREAKPROGRESS10:
			return 72;
	}
}

int Atlas::getBlockTexIndex(BlockId blockId, BlockFace blockFace) {
	switch (blockId) {
	case BlockId::GRASS:
		switch (blockFace) {
		case BlockFace::RIGHT:
		case BlockFace::LEFT:
		case BlockFace::FRONT:
		case BlockFace::BACK:
			return 0;
		case BlockFace::TOP:
			return 24;
		case BlockFace::BOTTOM:
			return 48;
		}
		break;
	case BlockId::DIRT:
		return 72;
	case BlockId::STONE:
		return 96;
	case BlockId::SAND:
		return 120;
	case BlockId::SNOWY_GRASS:
		switch (blockFace) {
		case BlockFace::RIGHT:
		case BlockFace::LEFT:
		case BlockFace::FRONT:
		case BlockFace::BACK:
			return 144;
		case BlockFace::TOP:
			return 168;
		case BlockFace::BOTTOM:
			return 192;
		}
		break;
	case BlockId::OAK_LOG:
		switch (blockFace) {
		case BlockFace::RIGHT:
		case BlockFace::LEFT:
		case BlockFace::FRONT:
		case BlockFace::BACK:
			return 216;
		case BlockFace::TOP:
		case BlockFace::BOTTOM:
			return 240;
		}
		break;
	case BlockId::LEAVES:
		return 264;
		break;
	case BlockId::PLANK:
		return 288;
		break;
	}
	BOOST_LOG_TRIVIAL(warning) << "Returning -1";
	return -1;
}

int Atlas::getItemTexIndex(ItemId itemId) {
	switch (itemId) {
	case ItemId::STICK:
		return 312;
	case ItemId::WOODEN_AXE:
		return 336;
	case ItemId::WOODEN_HOE:
		return 360;
	case ItemId::WOODEN_PICKAXE:
		return 384;
	case ItemId::WOODEN_SHOVEL:
		return 408;
	case ItemId::WOODEN_SWORD:
		return 432;
	case ItemId::STONE_AXE:
		return 456;
	case ItemId::STONE_HOE:
		return 480;
	case ItemId::STONE_PICKAXE:
		return 504;
	case ItemId::STONE_SHOVEL:
		return 528;
	case ItemId::STONE_SWORD:
		return 552;
	}
	return 576;
}