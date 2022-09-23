#include "BlockSharedSpec.h"

BlockSharedSpec::BlockSharedSpec() :
	m_blockId(BlockId::NONE),
	m_displayName(""),
	m_isTransparent(false),
	m_isRenderable(false),
	m_blockHardness(1.0f) {
}

BlockId BlockSharedSpec::getBlockId() {
	return m_blockId;
}

ItemId BlockSharedSpec::getBlockItemId() {
	return m_blockItemId;
}

std::string& BlockSharedSpec::getDisplayName() {
	return m_displayName;
}

bool BlockSharedSpec::isTransparent() {
	return m_isTransparent;
}

bool BlockSharedSpec::isRenderable() {
	return m_isRenderable;
}

float BlockSharedSpec::getBlockHardness() {
	return m_blockHardness;
}

const bool BlockSharedSpec::isWeakTo(ItemId itemId) {
	bool isWeak = false;
	if (!m_itemWeaknesses.empty()) {
		for (int i = 0; (i < m_itemWeaknesses.size()) && !isWeak; i++) {
			if (m_itemWeaknesses.at(i) == itemId) {
				isWeak = true;
			}
		}
	}
	return isWeak;
}