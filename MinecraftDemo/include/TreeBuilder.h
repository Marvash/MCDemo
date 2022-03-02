#pragma once
#include "coreInclude.h"
#include "Biomes/TundraBiome.h"
#include "Biomes/TaigaBiome.h"
#include "Biomes/MountainsBiome.h"
#include "Biomes/ForestBiome.h"
#include "Biomes/PlainsBiome.h"
#include "Biomes/DesertBiome.h"
#include "Biomes/HillsBiome.h"
#include "Biomes/JungleBiome.h"
#include "Biomes/SavanaBiome.h"
#include "Cube.h"

class TreeBuilder {
public:
	TreeBuilder();

	static void buildForestTree(float treeY, float treeX, float treeZ, float chunkX, float chunkY, unsigned int chunkSideSize, float xTreeMin, float yTreeMin, Cube***& blockMatrix);
};