#pragma once
#include "Core/Biomes/Biome.h"
#include "BlockSharedSpec.h"
#include "Core/Services/ItemLibrary/IItem.h"

class Chunk;
class BlockManager;

class Block {

	friend class BlockManager;

public:
	~Block();
	Block();
	Block(BlockId blockId, Chunk* chunkRef, glm::vec3& offset);
	Chunk* getChunkRef();
	Biome* getBiomeRef();
	glm::vec3& getBlockCoordsOffset();
	void setBiomeRef(Biome* biome);
	BlockId getBlockId() const;
	void changeBlock(BlockId blockId);
private:
	static BlockManager* m_blockManager;
	BlockId m_blockId;
	Biome* m_biomeRef;
	Chunk* m_chunkRef;
	glm::vec3 m_offset;
};