#pragma once
#include "coreInclude.h"
#include "Biome.h"

class MountainsBiome : public Biome {
public:
	static MountainsBiome* instance();

	void loadConfiguration() override;
private:
	static MountainsBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	MountainsBiome();
};