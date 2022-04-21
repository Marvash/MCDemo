#pragma once
#include "Biome.h"

class TundraBiome : public Biome {
public:
	TundraBiome();

	PerlinNoiseGenerator m_treePerlinGen;
	unsigned long long m_treesXPerlinSeed;
	unsigned long long m_treesYPerlinSeed;
	unsigned int m_treeGridCellSide;
};