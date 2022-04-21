#pragma once
#include "Biome.h"

class HillsBiome : public Biome {
public:
	HillsBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};