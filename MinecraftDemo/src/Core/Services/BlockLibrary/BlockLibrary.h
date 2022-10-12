#pragma once
#include "BlockIdEnum.h"
#include "BlockSharedSpec.h"
#include "DroppableBlockSharedSpec.h"
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
#include <map>

class CoreServiceLocator;

class BlockLibrary {
public:
	BlockLibrary(CoreServiceLocator* coreServiceLocator);
	~BlockLibrary();
	BlockSharedSpec* getBlockSpecification(BlockId blockId);
	DroppableBlockSharedSpec* getDroppableBlockSpecification(BlockId blockId);
private:
	void generateBlockSpecifications();
	void generateDroppableBlockSpecifications();
	CoreServiceLocator* m_coreServiceLocator;
	std::map<BlockId, BlockSharedSpec*> m_blockSpecifications;
	std::map<BlockId, DroppableBlockSharedSpec*> m_droppableBlockSpecifications;
};