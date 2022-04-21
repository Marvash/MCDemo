#pragma once
#include "Biome.h"

class ForestBiome : public Biome {
public:
	ForestBiome();

	unsigned int m_treeGridCellSide;
	PerlinNoiseGenerator m_treesXPerlinGen;
	PerlinNoiseGenerator m_treesYPerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
};