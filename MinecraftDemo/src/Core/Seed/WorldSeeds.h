#pragma once

class WorldSeeds
{
public:
	WorldSeeds();

	unsigned long long temperatureSeed{ 0 };
	unsigned long long humiditySeed{ 0 };

	unsigned long long DesertBiomeSeed{ 0 };
	unsigned long long ForestBiomeSeed{ 0 };
	unsigned long long HillsBiomeSeed{ 0 };
	unsigned long long JungleBiomeSeed{ 0 };
	unsigned long long MountainsBiomeSeed{ 0 };
	unsigned long long PlainsBiomeSeed{ 0 };
	unsigned long long SavanaBiomeSeed{ 0 };
	unsigned long long TaigaBiomeSeed{ 0 };
	unsigned long long TundraBiomeSeed{ 0 };

	unsigned long long ForestTreesXSeed{ 0 };
	unsigned long long ForestTreesYSeed{ 0 };

};

