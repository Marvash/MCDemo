#pragma once
#include "Biome.h"

class MountainsBiome : public Biome {
public:
	MountainsBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};