#pragma once
#include "Core/Game/Atlas/Atlas.h"
#include "Core/Game/Biomes/BiomeManager.h"
#include "Core/Game/Chunk/ChunkManager.h"

class GameServiceLocator
{
public:
	GameServiceLocator();

	Atlas* getAtlas();
	BiomeManager* getBiomeManager();
	ChunkManager* getChunkManager();

	void provide(Atlas* atlas);
	void provide(BiomeManager* biomeManager);
	void provide(ChunkManager* chunkManager);
private:
	Atlas* m_atlas;
	BiomeManager* m_biomeManager;
	ChunkManager* m_chunkManager;
};

