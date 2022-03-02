#include "Biomes/Biome.h"

Biome::Biome() : baseBiomePerlinGen(), hasTrees(false) {

}

float Biome::getBlockHeight(float x, float y) {
	float currentAmplitude = amplitude;
	float currentFrequency = frequency;
	float finalHeight = baseHeight;
	for (int i = 0; i < terrainDetailLevels; i++) {
		if (currentAmplitude > 0.0f) {
			finalHeight += currentAmplitude * baseBiomePerlinGen.getValue(x * currentFrequency, y * currentFrequency);
			currentAmplitude = currentAmplitude / 2.0f;
			currentFrequency = currentFrequency * 2.0f;
		}
	}
	return finalHeight;
}

void Biome::initBiome() {
	baseBiomePerlinGen.setSeed(seed);
	baseBiomePerlinGen.setPeriod(period);
}