#include "Biome.h"

Biome::Biome() : 
	m_baseBiomePerlinGen(),
	m_hasTrees(false) {

}

void Biome::initBiome() {
	m_baseBiomePerlinGen.setSeed(m_seed);
	m_baseBiomePerlinGen.setPeriod(m_period);
}

Biome::~Biome() {

}