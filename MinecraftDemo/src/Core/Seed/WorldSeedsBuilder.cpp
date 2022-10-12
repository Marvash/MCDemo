#include "WorldSeedsBuilder.h"



WorldSeedsBuilder::WorldSeedsBuilder() {

}

void WorldSeedsBuilder::reset() {
	m_result = new WorldSeeds();
}

void WorldSeedsBuilder::generateSeeds() {
	// TODO: IMPLEMENT SEED GENERATION
}

void WorldSeedsBuilder::loadSeeds() {
	m_result->temperatureSeed = 1234567;
	m_result->humiditySeed = 7654321;

	m_result->DesertBiomeSeed = 4444;
	m_result->ForestBiomeSeed = 8888;
	m_result->HillsBiomeSeed = 6666;
	m_result->JungleBiomeSeed = 9999;
	m_result->MountainsBiomeSeed = 5555;
	m_result->PlainsBiomeSeed = 7777;
	m_result->SavanaBiomeSeed = 3333;
	m_result->TaigaBiomeSeed = 2222;
	m_result->TundraBiomeSeed = 1111;

	m_result->ForestTreesXSeed = 4688831543253;
	m_result->ForestTreesYSeed = 76411553252;
}