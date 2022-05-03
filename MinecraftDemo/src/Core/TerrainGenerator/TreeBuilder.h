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
#include "Core/Cube/Cube.h"

class TreeBuilder {
public:
	TreeBuilder();

	static void buildForestTree(float treeY, float treeX, float treeZ, float chunkX, float chunkY, unsigned int chunkSideSize, float xTreeMin, float yTreeMin, Cube***& blockMatrix);
};