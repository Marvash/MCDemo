#pragma once
#include "Biome.h"

class TaigaBiome : public Biome {
public:
	TaigaBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};