#pragma once
#include "BlockIdEnum.h"
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include <string>
#include <vector>
#include <map>

class BlockSharedSpec {

	friend class BlockLibrary;

public:
	BlockSharedSpec();

	BlockId getBlockId();
	ItemId getBlockItemId();
	std::string& getDisplayName();
	bool isTransparent();
	bool isRenderable();
	float getBlockHardness();
	const bool isWeakTo(ItemId itemId);

private:
	BlockId m_blockId;
	ItemId m_blockItemId;
	std::string m_displayName;
	bool m_isTransparent;
	bool m_isRenderable;
	float m_blockHardness;
	std::vector<ItemId> m_itemWeaknesses;
};