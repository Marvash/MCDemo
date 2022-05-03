#pragma once
#include "Biome.h"

class PlainsBiome : public Biome {
public:
	PlainsBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};