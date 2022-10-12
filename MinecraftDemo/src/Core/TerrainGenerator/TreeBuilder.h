#pragma once
#include "Core/Biomes/TundraBiome.h"
#include "Core/Biomes/TaigaBiome.h"
#include "Core/Biomes/MountainsBiome.h"
#include "Core/Biomes/ForestBiome.h"
#include "Core/Biomes/PlainsBiome.h"
#include "Core/Biomes/DesertBiome.h"
#include "Core/Biomes/HillsBiome.h"
#include "Core/Biomes/JungleBiome.h"
#include "Core/Biomes/SavanaBiome.h"
#include "Core/Services/BlockLibrary/Block.h"
#include "Core/Services/BlockLibrary/BlockManager.h"

class TreeBuilder {
public:
	TreeBuilder(BlockManager* blockManager);

	void buildForestTree(float treeY, float treeX, float treeZ, float chunkX, float chunkY, unsigned int chunkSideSize, float xTreeMin, float yTreeMin, Block***& blockMatrix);
private:
	BlockManager* m_blockManager;
};