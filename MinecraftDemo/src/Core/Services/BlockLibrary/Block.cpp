#include "Block.h"
#include "Core/Chunk/Chunk.h"
#include "BlockManager.h"

BlockManager* Block::m_blockManager;

Block::Block() {}

Block::~Block() {}

Block::Block(BlockId blockId, Chunk* chunkRef, glm::vec3& offset) :
m_blockId(blockId),
m_chunkRef(chunkRef),
m_offset(offset) {

}

Chunk* Block::getChunkRef() {
	return m_chunkRef;
}

Biome* Block::getBiomeRef() {
	return m_biomeRef;
}

void Block::setBiomeRef(Biome* biome) {
	m_biomeRef = biome;
}

BlockId Block::getBlockId() const {
	return m_blockId;
}

glm::vec3& Block::getBlockCoordsOffset() {
	return m_offset;
}

void Block::changeBlock(BlockId blockId) {
	m_blockManager->changeBlock(this, blockId);
}