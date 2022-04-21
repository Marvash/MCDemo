#pragma once
#include "Core/Game/Biomes/TundraBiome.h"
#include "Core/Game/Biomes/TaigaBiome.h"
#include "Core/Game/Biomes/MountainsBiome.h"
#include "Core/Game/Biomes/ForestBiome.h"
#include "Core/Game/Biomes/PlainsBiome.h"
#include "Core/Game/Biomes/DesertBiome.h"
#include "Core/Game/Biomes/HillsBiome.h"
#include "Core/Game/Biomes/JungleBiome.h"
#include "Core/Game/Biomes/SavanaBiome.h"
#include "Core/Game/Cube/Cube.h"

class TreeBuilder {
public:
	TreeBuilder();

	static void buildForestTree(float treeY, float treeX, float treeZ, float chunkX, float chunkY, unsigned int chunkSideSize, float xTreeMin, float yTreeMin, Cube***& blockMatrix);
};