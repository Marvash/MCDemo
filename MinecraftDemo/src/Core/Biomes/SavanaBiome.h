#pragma once
#include "Biome.h"

class SavanaBiome : public Biome {
public:
	SavanaBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};