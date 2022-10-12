#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "Core/Biomes/Biome.h"
#include "Core/Biomes/DesertBiome.h"
#include "Core/Biomes/ForestBiome.h"
#include "Core/Biomes/HillsBiome.h"
#include "Core/Biomes/JungleBiome.h"
#include "Core/Biomes/MountainsBiome.h"
#include "Core/Biomes/PlainsBiome.h"
#include "Core/Biomes/SavanaBiome.h"
#include "Core/Biomes/TaigaBiome.h"
#include "Core/Biomes/TundraBiome.h"

class BiomeBuilder : public SpecializedBuilder<Biome> {
public:
	BiomeBuilder(const unsigned int& m_seaLevel);

	void loadDesertBiome();
	void loadForestBiome();
	void loadHillsBiome();
	void loadJungleBiome();
	void loadMountainsBiome();
	void loadPlainsBiome();
	void loadSavanaBiome();
	void loadTaigaBiome();
	void loadTundraBiome();
	void reset() override;
	void setSeaLevel(const unsigned int& seaLevel);
private:
	unsigned int m_seaLevel;
};