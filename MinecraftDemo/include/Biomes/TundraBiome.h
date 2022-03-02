#pragma once
#include "coreInclude.h"
#include "Biome.h"

class TundraBiome : public Biome {
public:
	static TundraBiome* instance();

	void loadConfiguration() override;

private:
	static TundraBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	TundraBiome();
};