#pragma once
#include "coreInclude.h"
#include "Biome.h"

class TaigaBiome : public Biome {
public:
	static TaigaBiome* instance();

	void loadConfiguration() override;
private:
	static TaigaBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	TaigaBiome();
};