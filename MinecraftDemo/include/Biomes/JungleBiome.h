#pragma once
#include "coreInclude.h"
#include "Biome.h"

class JungleBiome : public Biome {
public:
	static JungleBiome* instance();

	void loadConfiguration() override;
private:
	static JungleBiome* singleton;

	PerlinNoiseGenerator treePerlinGen;
	unsigned long long treesXPerlinSeed;
	unsigned long long treesYPerlinSeed;
	unsigned int treeGridCellSide;

	JungleBiome();
};