#pragma once
#include "coreInclude.h"
#include "Biome.h"

class HillsBiome : public Biome {
public:
	static HillsBiome* instance();

	void loadConfiguration() override;
private:
	static HillsBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	HillsBiome();
};