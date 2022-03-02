#pragma once
#include "coreInclude.h"
#include "Biome.h"

class ForestBiome : public Biome {
public:
	static ForestBiome* instance();

	unsigned int treeGridCellSide;
	PerlinNoiseGenerator treesXPerlinGen;
	PerlinNoiseGenerator treesYPerlinGen;

	void loadConfiguration() override;
private:
	static ForestBiome* singleton;

	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;

	ForestBiome();
	virtual void initBiome() override;
};