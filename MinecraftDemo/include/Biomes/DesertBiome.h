#pragma once
#include "coreInclude.h"
#include "Biome.h"

class DesertBiome : public Biome {
public:
	static DesertBiome* instance();

	void loadConfiguration() override;
private:
	static DesertBiome* singleton;

	DesertBiome();
};