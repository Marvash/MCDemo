#pragma once
#include "coreInclude.h"
#include "Biome.h"

class PlainsBiome : public Biome {
public:
	static PlainsBiome* instance();

	void loadConfiguration() override;
private:
	static PlainsBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	PlainsBiome();
};