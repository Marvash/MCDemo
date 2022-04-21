#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "Core/Game/Biomes/Biome.h"
#include "Core/Game/Biomes/DesertBiome.h"
#include "Core/Game/Biomes/ForestBiome.h"
#include "Core/Game/Biomes/HillsBiome.h"
#include "Core/Game/Biomes/JungleBiome.h"
#include "Core/Game/Biomes/MountainsBiome.h"
#include "Core/Game/Biomes/PlainsBiome.h"
#include "Core/Game/Biomes/SavanaBiome.h"
#include "Core/Game/Biomes/TaigaBiome.h"
#include "Core/Game/Biomes/TundraBiome.h"

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