#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(int chunkSideSize, int chunkHeight) : chunkSideSize(chunkSideSize), chunkHeight(chunkHeight), numBiomes(9) {

	populateBiomesArray();

	const unsigned long long temperatureSeed = 1234567;
	const unsigned long long humiditySeed = 7654321;

	terrainPerlinGen = PerlinNoiseGenerator();
	temperaturePerlinGen = PerlinNoiseGenerator(temperatureSeed);
	humidityPerlinGen = PerlinNoiseGenerator(humiditySeed);
}

void TerrainGenerator::populateBiomesArray() {
	biomes = new Biome[numBiomes];
	biomes[0] = Biome();
	biomes[0].biomeId = Biome::BiomeID::TUNDRA;
	biomes[0].name = "Tundra";
	biomes[0].minTemp = 0.0f;
	biomes[0].maxTemp = 0.3f;
	biomes[0].minHum = 0.0f;
	biomes[0].maxHum = 0.3f;
	biomes[0].period = 256;
	biomes[0].amplitude = 8.0f;
	biomes[0].frequency = 1.0f;
	biomes[0].baseHeight = seaLevel + 3;
	biomes[0].smoothGridSize = 8;
	biomes[0].terrainDetailLevels = 4;
	biomes[0].seed = 1111;

	biomes[1] = Biome();
	biomes[1].biomeId = Biome::BiomeID::TAIGA;
	biomes[1].name = "Taiga";
	biomes[1].minTemp = 0.3f;
	biomes[1].maxTemp = 0.5f;
	biomes[1].minHum = 0.0f;
	biomes[1].maxHum = 0.3f;
	biomes[1].period = 128;
	biomes[1].amplitude = 8.0f;
	biomes[1].frequency = 1.0f;
	biomes[1].baseHeight = seaLevel + 5;
	biomes[1].smoothGridSize = 8;
	biomes[1].terrainDetailLevels = 4;
	biomes[1].seed = 2222;

	biomes[2] = Biome();
	biomes[2].biomeId = Biome::BiomeID::SAVANA;
	biomes[2].name = "Savana";
	biomes[2].minTemp = 0.5f;
	biomes[2].maxTemp = 0.7f;
	biomes[2].minHum = 0.0f;
	biomes[2].maxHum = 0.3f;
	biomes[2].period = 128;
	biomes[2].amplitude = 8.0f;
	biomes[2].frequency = 1.0f;
	biomes[2].baseHeight = seaLevel + 5;
	biomes[2].smoothGridSize = 8;
	biomes[2].terrainDetailLevels = 4;
	biomes[2].seed = 3333;

	biomes[3] = Biome();
	biomes[3].biomeId = Biome::BiomeID::DESERT;
	biomes[3].name = "Desert";
	biomes[3].minTemp = 0.7f;
	biomes[3].maxTemp = 1.0f;
	biomes[3].minHum = 0.0f;
	biomes[3].maxHum = 0.3f;
	biomes[3].period = 256;
	biomes[3].amplitude = 8.0f;
	biomes[3].frequency = 1.0f;
	biomes[3].baseHeight = seaLevel + 3;
	biomes[3].smoothGridSize = 8;
	biomes[3].terrainDetailLevels = 4;
	biomes[3].seed = 4444;

	biomes[4] = Biome();
	biomes[4].biomeId = Biome::BiomeID::MOUNTAINS;
	biomes[4].name = "Mountains";
	biomes[4].minTemp = 0.3f;
	biomes[4].maxTemp = 0.5f;
	biomes[4].minHum = 0.3f;
	biomes[4].maxHum = 0.5f;
	biomes[4].period = 128;
	biomes[4].amplitude = 60.0f;
	biomes[4].frequency = 1.0f;
	biomes[4].baseHeight = seaLevel + 15;
	biomes[4].smoothGridSize = 8;
	biomes[4].terrainDetailLevels = 4;
	biomes[4].seed = 5555;

	biomes[5] = Biome();
	biomes[5].biomeId = Biome::BiomeID::HILLS;
	biomes[5].name = "Hills";
	biomes[5].minTemp = 0.5f;
	biomes[5].maxTemp = 0.7f;
	biomes[5].minHum = 0.3f;
	biomes[5].maxHum = 0.5f;
	biomes[5].period = 128;
	biomes[5].amplitude = 30.0f;
	biomes[5].frequency = 1.0f;
	biomes[5].baseHeight = seaLevel + 10;
	biomes[5].smoothGridSize = 8;
	biomes[5].terrainDetailLevels = 4;
	biomes[5].seed = 6666;

	biomes[6] = Biome();
	biomes[6].biomeId = Biome::BiomeID::PLAINS;
	biomes[6].name = "Plains";
	biomes[6].minTemp = 0.7f;
	biomes[6].maxTemp = 1.0f;
	biomes[6].minHum = 0.3f;
	biomes[6].maxHum = 0.5f;
	biomes[6].period = 128;
	biomes[6].amplitude = 5.0f;
	biomes[6].frequency = 1.0f;
	biomes[6].baseHeight = seaLevel + 8;
	biomes[6].smoothGridSize = 8;
	biomes[6].terrainDetailLevels = 4;
	biomes[6].seed = 7777;

	biomes[7] = Biome();
	biomes[7].biomeId = Biome::BiomeID::FOREST;
	biomes[7].name = "Forest";
	biomes[7].minTemp = 0.5f;
	biomes[7].maxTemp = 1.0f;
	biomes[7].minHum = 0.5f;
	biomes[7].maxHum = 0.8f;
	biomes[7].period = 64;
	biomes[7].amplitude = 8.0f;
	biomes[7].frequency = 1.0f;
	biomes[7].baseHeight = seaLevel + 8;
	biomes[7].smoothGridSize = 8;
	biomes[7].terrainDetailLevels = 4;
	biomes[7].seed = 8888;
	
	biomes[8] = Biome();
	biomes[8].biomeId = Biome::BiomeID::JUNGLE;
	biomes[8].name = "Jungle";
	biomes[8].minTemp = 0.8f;
	biomes[8].maxTemp = 1.0f;
	biomes[8].minHum = 0.8f;
	biomes[8].maxHum = 1.0f;
	biomes[8].period = 64;
	biomes[8].amplitude = 12.0f;
	biomes[8].frequency = 1.0f;
	biomes[8].baseHeight = seaLevel + 10;
	biomes[8].smoothGridSize = 8;
	biomes[8].terrainDetailLevels = 4;
	biomes[8].seed = 9999;
}

float TerrainGenerator::getHeight(float x, float y) {
	float baseWidth = x;
	float baseDepth = y;

	float temperaturePerlinValue = 0.0f;
	float humidityPerlinValue = 0.0f;
	int LODs = biomePerlinLODs;
	int biomePeriod = biomePerlinPeriod;
	float biomeFrequency = 1.0f;
	float biomeAmplitude = 1.0f;
	float normFactorToAdd = perlinNormFactor;
	float normFactor = 0.0f;
	for (int i = 0; i < LODs; i++) {
		temperaturePerlinValue += biomeAmplitude * temperaturePerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency, biomePeriod);
		humidityPerlinValue += biomeAmplitude * humidityPerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency, biomePeriod);
		biomeAmplitude = biomeAmplitude / 2.0f;
		biomeFrequency = biomeFrequency * 2;
		normFactor += normFactorToAdd;
		normFactorToAdd = normFactorToAdd / 2.0f;
	}
	float normTPV = (temperaturePerlinValue - (-normFactor)) / (normFactor - (-normFactor));
	float normMPV = (humidityPerlinValue - (-normFactor)) / (normFactor - (-normFactor));

	if (normTPV < 0.0f) {
		normTPV = 0.0f;
	}
	if (normMPV < 0.0f) {
		normMPV = 0.0f;
	}
	if (normTPV > 1.0f) {
		normTPV = 1.0f;
	}
	if (normMPV > 1.0f) {
		normMPV = 1.0f;
	}

	float scaledHumidity = normMPV * normTPV;

	Biome biome = biomes[(size_t)Biome::BiomeID::FOREST];
	Biome* neighbouringBiomes = new Biome[(numBiomes - (size_t)1)];
	int neighbourBiomesCount = 0;
	float mainBiomeFactor = 0.0f;

	for (int i = 0; i < numBiomes; i++) {
		float minTempDelta = glm::abs(normTPV - biomes[i].minTemp);
		float minHumDelta = glm::abs(scaledHumidity - biomes[i].minHum);
		float maxTempDelta = glm::abs(normTPV - biomes[i].maxTemp);
		float maxHumDelta = glm::abs(scaledHumidity - biomes[i].maxHum);
		// could be problematic near zero
		if (normTPV >= biomes[i].minTemp && normTPV <= biomes[i].maxTemp && scaledHumidity >= biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
			biome = biomes[i];
		}
		else if (minHumDelta <= biomeNeighbourInfluenceThreshold && minTempDelta <= biomeNeighbourInfluenceThreshold) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && minTempDelta <= biomeNeighbourInfluenceThreshold) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && maxTempDelta <= biomeNeighbourInfluenceThreshold) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= biomeNeighbourInfluenceThreshold && maxTempDelta <= biomeNeighbourInfluenceThreshold) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minTempDelta <= biomeNeighbourInfluenceThreshold && scaledHumidity > biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxTempDelta <= biomeNeighbourInfluenceThreshold && scaledHumidity > biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= biomeNeighbourInfluenceThreshold && normTPV > biomes[i].minTemp && normTPV <= biomes[i].maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && normTPV > biomes[i].minTemp && normTPV <= biomes[i].maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}

	}

	std::cout << "Current position is x: " << baseWidth << " y: " << baseDepth << " biome: " << biome.name << std::endl;
	std::cout << "Temp: " << normTPV << " Hum: " << scaledHumidity << std::endl;
	std::cout << neighbourBiomesCount << " neighbours detected" << std::endl;
	float height = 0.0f;
	if (neighbourBiomesCount > 0) {
		float* sampleHeights = new float[4];
		float* sampleCoords = new float[4];
		getBilinearSmoothingGridCoordinates(baseWidth, baseDepth, sampleCoords);

		float x = 0.0f;
		float y = 0.0f;
		for (int k = 0; k < 4; k++) {
			switch (k) {
			case 0:
				x = sampleCoords[0];
				y = sampleCoords[3];
				break;
			case 1:
				x = sampleCoords[1];
				y = sampleCoords[3];
				break;
			case 2:
				x = sampleCoords[1];
				y = sampleCoords[2];
				break;
			case 3:
				x = sampleCoords[0];
				y = sampleCoords[2];
				break;
			}
			int tmpLODs = biomePerlinLODs;
			int tmpBiomePeriod = biomePerlinPeriod;
			float tmpBiomeAmplitude = 1.0f;
			float tmpBiomeFrequency = 1.0f;
			float tmpNormFactorToAdd = perlinNormFactor;
			float tmpNormFactor = 0.0f;
			float tmpTemperaturePerlinValue = 0.0f;
			float tmpHumidityPerlinValue = 0.0f;
			for (int i = 0; i < tmpLODs; i++) {
				tmpTemperaturePerlinValue += tmpBiomeAmplitude * temperaturePerlinGen.getValue(x * tmpBiomeFrequency, y * tmpBiomeFrequency, tmpBiomePeriod);
				tmpHumidityPerlinValue += tmpBiomeAmplitude * humidityPerlinGen.getValue(x * tmpBiomeFrequency, y * tmpBiomeFrequency, tmpBiomePeriod);
				tmpBiomeAmplitude = tmpBiomeAmplitude / 2.0f;
				tmpBiomeFrequency = tmpBiomeFrequency * 2.0f;
				tmpNormFactor += tmpNormFactorToAdd;
				tmpNormFactorToAdd = tmpNormFactorToAdd / 2.0f;
			}
			float tmpNormTPV = (tmpTemperaturePerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));
			float tmpNormMPV = (tmpHumidityPerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));

			if (tmpNormTPV < 0.0f) {
				tmpNormTPV = 0.0f;
			}
			if (tmpNormMPV < 0.0f) {
				tmpNormMPV = 0.0f;
			}
			if (tmpNormTPV > 1.0f) {
				tmpNormTPV = 1.0f;
			}
			if (tmpNormMPV > 1.0f) {
				tmpNormMPV = 1.0f;
			}
			Biome tmpBiome = biomes[(size_t)Biome::BiomeID::FOREST];
			float tmpScaledHumidity = tmpNormMPV * tmpNormTPV;
			for (int i = 0; i < numBiomes; i++) {
				if (tmpNormTPV >= biomes[i].minTemp && tmpNormTPV <= biomes[i].maxTemp && tmpScaledHumidity >= biomes[i].minHum && tmpScaledHumidity <= biomes[i].maxHum) {
					tmpBiome = biomes[i];
					break;
				}
			}
			
			int currentlevels = tmpBiome.terrainDetailLevels;
			float currentAmplitude = tmpBiome.amplitude;
			float currentFrequency = tmpBiome.frequency;
			int currentPeriod = tmpBiome.period;
			float currentBiomeBaseHeight = biome.baseHeight;
			sampleHeights[k] = currentBiomeBaseHeight;
			for (int l = 0; l < currentlevels; l++) {
				if (currentAmplitude > 0.0f) {
					sampleHeights[k] += currentAmplitude * terrainPerlinGen.getValue(tmpBiome.seed, x * currentFrequency, y * currentFrequency, currentPeriod);
					currentAmplitude = currentAmplitude / 2.0f;
					currentFrequency = currentFrequency * 2.0f;
				}
			}
			std::cout << "Sample " << k << " x: " << x << " y: " << y << " biome: " << tmpBiome.name << " height: " << sampleHeights[k] << std::endl;
		}
		height = bilinearFilter(baseWidth, baseDepth, sampleHeights, sampleCoords);
		std::cout << "Bilinear filtering: " << height << std::endl;
		delete[] sampleHeights;
		delete[] sampleCoords;
	}
	else {
		std::cout << "No neighbours" << std::endl;
		int levels = biome.terrainDetailLevels;
		float amplitude = biome.amplitude;
		float frequency = biome.frequency;
		int period = biome.period;
		float biomeBaseHeight = biome.baseHeight;
		for (int k = 0; k < levels; k++) {
			if (amplitude > 0.0f) {
				height += amplitude * terrainPerlinGen.getValue(biome.seed, baseWidth * frequency, baseDepth * frequency, period);
				amplitude = amplitude / 2.0f;
				frequency = frequency * 2.0f;
			}
		}
		height += biomeBaseHeight;
	}

	delete[] neighbouringBiomes;

	return height;
}

void TerrainGenerator::generateChunk(Cube*** &blockMatrix, glm::vec3& chunkPosition, Chunk* &parentChunk) {

	for (int j = 0; j < chunkSideSize; j++) {
		for (int w = 0; w < chunkSideSize; w++) {
			float baseWidth = chunkPosition.x + ((j - (chunkSideSize / 2)) - 0.5f);
			float baseDepth = chunkPosition.z + ((w - (chunkSideSize / 2)) - 0.5f);

			float temperaturePerlinValue = 0.0f;
			float humidityPerlinValue = 0.0f;
			int LODs = biomePerlinLODs;
			int biomePeriod = biomePerlinPeriod;
			float biomeFrequency = 1.0f;
			float biomeAmplitude = 1.0f;
			float normFactorToAdd = perlinNormFactor;
			float normFactor = 0.0f;
			for (int i = 0; i < LODs; i++) {
				temperaturePerlinValue += biomeAmplitude * temperaturePerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency, biomePeriod);
				humidityPerlinValue += biomeAmplitude * humidityPerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency, biomePeriod);
				biomeAmplitude = biomeAmplitude / 2.0f;
				biomeFrequency = biomeFrequency * 2;
				normFactor += normFactorToAdd;
				normFactorToAdd = normFactorToAdd / 2.0f;
			}
			float normTPV = (temperaturePerlinValue - (-normFactor)) / (normFactor - (-normFactor));
			float normMPV = (humidityPerlinValue - (-normFactor)) / (normFactor - (-normFactor));

			if (normTPV < 0.0f) {
				normTPV = 0.0f;
			}
			if (normMPV < 0.0f) {
				normMPV = 0.0f;
			}
			if (normTPV > 1.0f) {
				normTPV = 1.0f;
			}
			if (normMPV > 1.0f) {
				normMPV = 1.0f;
			}

			float scaledHumidity = normMPV * normTPV;

			Biome biome = biomes[(size_t)Biome::BiomeID::FOREST];
			Biome* neighbouringBiomes = new Biome[(numBiomes - (size_t)1)];
			int neighbourBiomesCount = 0;
			float mainBiomeFactor = 0.0f;

			for (int i = 0; i < numBiomes; i++) {
				float minTempDelta = glm::abs(normTPV - biomes[i].minTemp);
				float minHumDelta = glm::abs(scaledHumidity - biomes[i].minHum);
				float maxTempDelta = glm::abs(normTPV - biomes[i].maxTemp);
				float maxHumDelta = glm::abs(scaledHumidity - biomes[i].maxHum);
				// could be problematic near zero
				if (normTPV >= biomes[i].minTemp && normTPV <= biomes[i].maxTemp && scaledHumidity >= biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
					biome = biomes[i];
				} 
				else if (minHumDelta <= biomeNeighbourInfluenceThreshold && minTempDelta <= biomeNeighbourInfluenceThreshold) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && minTempDelta <= biomeNeighbourInfluenceThreshold) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && maxTempDelta <= biomeNeighbourInfluenceThreshold) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (minHumDelta <= biomeNeighbourInfluenceThreshold && maxTempDelta <= biomeNeighbourInfluenceThreshold) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (minTempDelta <= biomeNeighbourInfluenceThreshold && scaledHumidity > biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (maxTempDelta <= biomeNeighbourInfluenceThreshold && scaledHumidity > biomes[i].minHum && scaledHumidity <= biomes[i].maxHum) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (minHumDelta <= biomeNeighbourInfluenceThreshold && normTPV > biomes[i].minTemp && normTPV <= biomes[i].maxTemp) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				else if (maxHumDelta <= biomeNeighbourInfluenceThreshold && normTPV > biomes[i].minTemp && normTPV <= biomes[i].maxTemp) {
					neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
				}
				
			}
			
			float height = 0.0f;
			if (neighbourBiomesCount > 0) {
				float* sampleHeights = new float[4];
				float* sampleCoords = new float[4];
				getBilinearSmoothingGridCoordinates(baseWidth, baseDepth, sampleCoords);

				float x = 0.0f;
				float y = 0.0f;
				for (int k = 0; k < 4; k++) {
					switch (k) {
					case 0:
						x = sampleCoords[0];
						y = sampleCoords[3];
						break;
					case 1:
						x = sampleCoords[1];
						y = sampleCoords[3];
						break;
					case 2:
						x = sampleCoords[1];
						y = sampleCoords[2];
						break;
					case 3:
						x = sampleCoords[0];
						y = sampleCoords[2];
						break;
					}
					int tmpLODs = biomePerlinLODs;
					int tmpBiomePeriod = biomePerlinPeriod;
					float tmpBiomeAmplitude = 1.0f;
					float tmpBiomeFrequency = 1.0f;
					float tmpNormFactorToAdd = perlinNormFactor;
					float tmpNormFactor = 0.0f;
					float tmpTemperaturePerlinValue = 0.0f;
					float tmpHumidityPerlinValue = 0.0f;
					for (int i = 0; i < tmpLODs; i++) {
						tmpTemperaturePerlinValue += tmpBiomeAmplitude * temperaturePerlinGen.getValue(x * tmpBiomeFrequency, y * tmpBiomeFrequency, tmpBiomePeriod);
						tmpHumidityPerlinValue += tmpBiomeAmplitude * humidityPerlinGen.getValue(x * tmpBiomeFrequency, y * tmpBiomeFrequency, tmpBiomePeriod);
						tmpBiomeAmplitude = tmpBiomeAmplitude / 2.0f;
						tmpBiomeFrequency = tmpBiomeFrequency * 2.0f;
						tmpNormFactor += tmpNormFactorToAdd;
						tmpNormFactorToAdd = tmpNormFactorToAdd / 2.0f;
					}
					float tmpNormTPV = (tmpTemperaturePerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));
					float tmpNormMPV = (tmpHumidityPerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));

					if (tmpNormTPV < 0.0f) {
						tmpNormTPV = 0.0f;
					}
					if (tmpNormMPV < 0.0f) {
						tmpNormMPV = 0.0f;
					}
					if (tmpNormTPV > 1.0f) {
						tmpNormTPV = 1.0f;
					}
					if (tmpNormMPV > 1.0f) {
						tmpNormMPV = 1.0f;
					}
					Biome tmpBiome = biomes[(size_t)Biome::BiomeID::FOREST];
					float tmpScaledHumidity = tmpNormMPV * tmpNormTPV;
					for (int i = 0; i < numBiomes; i++) {
						if (tmpNormTPV >= biomes[i].minTemp && tmpNormTPV <= biomes[i].maxTemp && tmpScaledHumidity >= biomes[i].minHum && tmpScaledHumidity <= biomes[i].maxHum) {
							tmpBiome = biomes[i];
							break;
						}
					}
					
					int currentlevels = tmpBiome.terrainDetailLevels;
					float currentAmplitude = tmpBiome.amplitude;
					float currentFrequency = tmpBiome.frequency;
					int currentPeriod = tmpBiome.period;
					float currentBiomeBaseHeight = tmpBiome.baseHeight;
					sampleHeights[k] = currentBiomeBaseHeight;
					for (int l = 0; l < currentlevels; l++) {
						if (currentAmplitude > 0.0f) {
							sampleHeights[k] += currentAmplitude * terrainPerlinGen.getValue(tmpBiome.seed, x * currentFrequency, y * currentFrequency, currentPeriod);
							currentAmplitude = currentAmplitude / 2.0f;
							currentFrequency = currentFrequency * 2.0f;
						}
					}
				}
				height = bilinearFilter(baseWidth, baseDepth, sampleHeights, sampleCoords);
				delete[] sampleHeights;
				delete[] sampleCoords;
				/*
				int filterRadius = 4;
				float* sampleHeights = new float[4];
				float* sampleCoords = new float[2];
				sampleCoords[0] = -(float)filterRadius;
				sampleCoords[1] = +(float)filterRadius;
				float x = 0.0f;
				float y = 0.0f;
				for (int k = 0; k < 4; k++) {
					switch (k) {
					case 0:
						x = chunkPosition.x - (float)filterRadius;
						y = chunkPosition.z - (float)filterRadius;
						break;
					case 1:
						x = chunkPosition.x + (float)filterRadius;
						y = chunkPosition.z - (float)filterRadius;
						break;
					case 2:
						x = chunkPosition.x + (float)filterRadius;
						y = chunkPosition.z + (float)filterRadius;
						break;
					case 3:
						x = chunkPosition.x - (float)filterRadius;
						y = chunkPosition.z + (float)filterRadius;
						break;
					}
					int tmpLODs = biomePerlinLODs;
					int tmpBiomeFrequency = biomePerlinFrequency;
					float tmpBiomeAmplitude = 1.0f;
					float tmpNormFactorToAdd = perlinNormFactor;
					float tmpNormFactor = 0.0f;
					float tmpTemperaturePerlinValue = 0.0f;
					float tmpHumidityPerlinValue = 0.0f;
					for (int i = 0; i < tmpLODs; i++) {
						tmpTemperaturePerlinValue += temperaturePerlinGen.getValue(x, y, tmpBiomeFrequency, tmpBiomeAmplitude);
						tmpHumidityPerlinValue += humidityPerlinGen.getValue(x, y, tmpBiomeFrequency, tmpBiomeAmplitude);
						tmpBiomeAmplitude = tmpBiomeAmplitude / 2.0f;
						tmpBiomeFrequency = tmpBiomeFrequency / 2;
						tmpNormFactor += tmpNormFactorToAdd;
						tmpNormFactorToAdd = tmpNormFactorToAdd / 2.0f;
					}
					float tmpNormTPV = (tmpTemperaturePerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));
					float tmpNormMPV = (tmpHumidityPerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));

					if (tmpNormTPV < 0.0f) {
						tmpNormTPV = 0.0f;
					}
					if (tmpNormMPV < 0.0f) {
						tmpNormMPV = 0.0f;
					}
					if (tmpNormTPV > 1.0f) {
						tmpNormTPV = 1.0f;
					}
					if (tmpNormMPV > 1.0f) {
						tmpNormMPV = 1.0f;
					}
					Biome tmpBiome;
					float tmpScaledHumidity = tmpNormMPV * tmpNormTPV;
					for (int i = 0; i < numBiomes; i++) {
						if (tmpNormTPV > biomes[i].minTemp && tmpNormTPV <= biomes[i].maxTemp && tmpScaledHumidity > biomes[i].minHum && tmpScaledHumidity <= biomes[i].maxHum) {
							tmpBiome = biomes[i];
						}
					}
					sampleHeights[k] = 0.0f;
					int currentlevels = tmpBiome.terrainDetail;
					float currentAmplitude = tmpBiome.amplitude;
					int currentFrequency = tmpBiome.frequency;
					for (int l = 0; l < currentlevels; l++) {
						if (currentAmplitude > 0.0f && currentFrequency > 1) {
							sampleHeights[k] += terrainPerlinGen.getValue(tmpBiome.seed, x, y, currentFrequency, currentAmplitude);
							currentAmplitude = currentAmplitude / 2.0f;
							currentFrequency = currentFrequency / 2;
						}
					}
				}
				
				height = bilinearFilter(baseWidth, baseDepth, sampleHeights, sampleCoords);
				delete[] sampleHeights;
				delete[] sampleCoords;
				*/
				// Smooth filter ridge implementation, too expensive
				/*
				float avgSum = 0.0f;
				int smoothRadius = 20;
				int totalSamples = 0;
				float** heightArray = new float*[smoothRadius];
				for (int k = 0; k < smoothRadius; k++) {
					heightArray[k] = new float[smoothRadius];
				}
				for (int k = 0; k < smoothRadius; k++) {
					for (int z = 0; z < smoothRadius; z++) {
						if ((k == 0 || k == 19 || k == 5 || k == 15 || k == 10) && (z == 0 || z == 19 || z == 5 || z == 15 || z == 10)) {
							totalSamples++;
							int tmpLODs = biomePerlinLODs;
							int tmpBiomeFrequency = biomePerlinFrequency;
							float tmpBiomeAmplitude = 1.0f;
							float tmpNormFactorToAdd = perlinNormFactor;
							float tmpNormFactor = 0.0f;
							float tmpTemperaturePerlinValue = 0.0f;
							float tmpHumidityPerlinValue = 0.0f;
							float tmpBaseWidth = baseWidth + ((float)k - (glm::floor(smoothRadius / 2.0f)));
							float tmpBaseDepth = baseDepth + ((float)z - (glm::floor(smoothRadius / 2.0f)));
							for (int i = 0; i < tmpLODs; i++) {
								tmpTemperaturePerlinValue += temperaturePerlinGen.getValue(tmpBaseWidth, tmpBaseDepth, tmpBiomeFrequency, tmpBiomeAmplitude);
								tmpHumidityPerlinValue += humidityPerlinGen.getValue(tmpBaseWidth, tmpBaseDepth, tmpBiomeFrequency, tmpBiomeAmplitude);
								tmpBiomeAmplitude = tmpBiomeAmplitude / 2.0f;
								tmpBiomeFrequency = tmpBiomeFrequency / 2;
								tmpNormFactor += tmpNormFactorToAdd;
								tmpNormFactorToAdd = tmpNormFactorToAdd / 2.0f;
							}
							float tmpNormTPV = (tmpTemperaturePerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));
							float tmpNormMPV = (tmpHumidityPerlinValue - (-tmpNormFactor)) / (tmpNormFactor - (-tmpNormFactor));

							if (tmpNormTPV < 0.0f) {
								tmpNormTPV = 0.0f;
							}
							if (tmpNormMPV < 0.0f) {
								tmpNormMPV = 0.0f;
							}
							if (tmpNormTPV > 1.0f) {
								tmpNormTPV = 1.0f;
							}
							if (tmpNormMPV > 1.0f) {
								tmpNormMPV = 1.0f;
							}
							Biome tmpBiome;
							float tmpScaledHumidity = tmpNormMPV * tmpNormTPV;
							for (int i = 0; i < numBiomes; i++) {
								if (tmpNormTPV > biomes[i].minTemp && tmpNormTPV <= biomes[i].maxTemp && tmpScaledHumidity > biomes[i].minHum && tmpScaledHumidity <= biomes[i].maxHum) {
									tmpBiome = biomes[i];
								}
							}
							int currentlevels = tmpBiome.terrainDetail;
							float currentAmplitude = tmpBiome.amplitude;
							int currentFrequency = tmpBiome.frequency;
							for (int l = 0; l < currentlevels; l++) {
								if (currentAmplitude > 0.0f && currentFrequency > 1) {
									avgSum += terrainPerlinGen.getValue(tmpBiome.seed, tmpBaseWidth, tmpBaseDepth, currentFrequency, currentAmplitude);
									currentAmplitude = currentAmplitude / 2.0f;
									currentFrequency = currentFrequency / 2;
								}
							}
						}
					}
				}
				height = avgSum / totalSamples;
				*/
			}
			else {
				int levels = biome.terrainDetailLevels;
				float amplitude = biome.amplitude;
				float frequency = biome.frequency;
				int period = biome.period;
				float biomeBaseHeight = biome.baseHeight;
				for (int k = 0; k < levels; k++) {
					if (amplitude > 0.0f) {
						height += amplitude * terrainPerlinGen.getValue(biome.seed, baseWidth * frequency, baseDepth * frequency, period);
						amplitude = amplitude / 2.0f;
						frequency = frequency * 2.0f;
					}
				}
				height += biomeBaseHeight;
			}

			delete[] neighbouringBiomes;

			int finalHeight = (int)height;
			int dirtHeight = 70;
			for (int i = 0; i < chunkHeight; i++) { 
				if (i <= finalHeight) {
					if (i < dirtHeight) {
						blockMatrix[i][j][w] = Cube(Cube::CubeId::STONE_BLOCK, parentChunk, biome.biomeId);
					}
					else if (i >= dirtHeight && i < finalHeight) {
						if (biome.biomeId == Biome::BiomeID::DESERT) {
							blockMatrix[i][j][w] = Cube(Cube::CubeId::SAND_BLOCK, parentChunk, biome.biomeId);
						}
						else {
							blockMatrix[i][j][w] = Cube(Cube::CubeId::DIRT_BLOCK, parentChunk, biome.biomeId);
						}
					}
					else if (i == finalHeight) {
						if (biome.biomeId == Biome::BiomeID::DESERT) {
							blockMatrix[i][j][w] = Cube(Cube::CubeId::SAND_BLOCK, parentChunk, biome.biomeId);
						}
						else if (biome.biomeId == Biome::BiomeID::TUNDRA) {
							blockMatrix[i][j][w] = Cube(Cube::CubeId::SNOWY_GRASS_BLOCK, parentChunk, biome.biomeId);
						}
						else {
							blockMatrix[i][j][w] = Cube(Cube::CubeId::GRASS_BLOCK, parentChunk, biome.biomeId);
						}
						
					}
				}
				else {
					blockMatrix[i][j][w] = Cube(Cube::CubeId::AIR_BLOCK, parentChunk, biome.biomeId);
				}
			}
		}
	}
}

float TerrainGenerator::bilinearFilter(float x, float y, float* samples, float* corners) {
	float a = samples[0];
	float b = samples[1];
	float c = samples[2];
	float d = samples[3];

	float x1 = corners[0];
	float x2 = corners[1];
	float y1 = corners[2];
	float y2 = corners[3];

	float intermediateLerpY1 = (((x2 - x) / (x2 - x1)) * d) + (((x - x1) / (x2 - x1)) * c);
	float intermediateLerpY2 = (((x2 - x) / (x2 - x1)) * a) + (((x - x1) / (x2 - x1)) * b);

	float finalLerp = (((y2 - y) / (y2 - y1)) * intermediateLerpY1) + (((y - y1) / (y2 - y1)) * intermediateLerpY2);

	return finalLerp;
}

void TerrainGenerator::getBilinearSmoothingGridCoordinates(float x, float y, float* corners, int smoothingGridCellSize) {
	if (x >= 0) {
		corners[0] = (float)(((int)x / smoothingGridCellSize) * smoothingGridCellSize);
		corners[1] = corners[0] + smoothingGridCellSize;
	}
	else {
		corners[1] = (float)(((int)x / smoothingGridCellSize) * smoothingGridCellSize);
		corners[0] = corners[1] - smoothingGridCellSize;
	}
	if (y > 0) {
		corners[3] = (float)(((int)y / smoothingGridCellSize) * smoothingGridCellSize);
		corners[2] = corners[3] + smoothingGridCellSize;
	}
	else {
		corners[2] = (float)(((int)y / smoothingGridCellSize) * smoothingGridCellSize);
		corners[3] = corners[2] - smoothingGridCellSize;
	}
	
}