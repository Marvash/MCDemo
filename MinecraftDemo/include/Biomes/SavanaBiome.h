#pragma once
#include "coreInclude.h"
#include "Biome.h"

class SavanaBiome : public Biome {
public:
	static SavanaBiome* instance();

	void loadConfiguration() override;

private:
	static SavanaBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	SavanaBiome();
};