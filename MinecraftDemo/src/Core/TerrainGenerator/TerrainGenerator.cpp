#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(BiomeLibrary* biomeManager, BlockManager* blockManager, int chunkSideSize, int chunkHeight) :
	m_chunkSideSize(chunkSideSize), 
	m_chunkHeight(chunkHeight), 
	m_treeChunkOffset(8), 
	m_biomeManager(biomeManager),
	m_blockManager(blockManager),
	m_treeBuilder(new TreeBuilder(blockManager)) {

	m_temperaturePerlinGen = PerlinNoiseGenerator();
	m_temperaturePerlinGen.setSeed(m_temperatureSeed);
	m_temperaturePerlinGen.setPeriod(BIOME_PERLIN_PERIOD);
	m_humidityPerlinGen = PerlinNoiseGenerator();
	m_humidityPerlinGen.setSeed(m_humiditySeed);
	m_humidityPerlinGen.setPeriod(BIOME_PERLIN_PERIOD);
}

TerrainGenerator::~TerrainGenerator() {
	delete m_treeBuilder;
}

float TerrainGenerator::getBlockHeight(Biome* biome, float x, float y) {
	float currentAmplitude = biome->m_amplitude;
	float currentFrequency = biome->m_frequency;
	float finalHeight = biome->m_baseHeight;
	for (int i = 0; i < biome->m_terrainDetailLevels; i++) {
		if (currentAmplitude > 0.0f) {
			finalHeight += currentAmplitude * biome->m_baseBiomePerlinGen.getValue(x * currentFrequency, y * currentFrequency);
			currentAmplitude = currentAmplitude / 2.0f;
			currentFrequency = currentFrequency * 2.0f;
		}
	}
	return finalHeight;
}

float TerrainGenerator::getDebugHeight(float x, float y) {
	Biome** biomes = m_biomeManager->getBiomes();
	unsigned int biomesCount = m_biomeManager->getBiomesCount();

	float baseWidth = x;
	float baseDepth = y;

	float temperaturePerlinValue = 0.0f;
	float humidityPerlinValue = 0.0f;
	int LODs = BIOME_PERLIN_LODS;
	float biomeFrequency = 1.0f;
	float biomeAmplitude = 1.0f;
	float normFactorToAdd = PERLIN_NORM_FACTOR;
	float normFactor = 0.0f;
	for (int i = 0; i < LODs; i++) {
		temperaturePerlinValue += biomeAmplitude * m_temperaturePerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency);
		humidityPerlinValue += biomeAmplitude * m_humidityPerlinGen.getValue(baseWidth * biomeFrequency, baseDepth * biomeFrequency);
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

	Biome* biome = biomes[7];
	Biome** neighbouringBiomes = new Biome*[(biomesCount - 1)];
	int neighbourBiomesCount = 0;
	float mainBiomeFactor = 0.0f;

	for (int i = 0; i < biomesCount; i++) {
		float minTempDelta = glm::abs(normTPV - biomes[i]->m_minTemp);
		float minHumDelta = glm::abs(scaledHumidity - biomes[i]->m_minHum);
		float maxTempDelta = glm::abs(normTPV - biomes[i]->m_maxTemp);
		float maxHumDelta = glm::abs(scaledHumidity - biomes[i]->m_maxHum);
		// could be problematic near zero
		if (normTPV >= biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp && scaledHumidity >= biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			biome = biomes[i];
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && scaledHumidity > biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && scaledHumidity > biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && normTPV > biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && normTPV > biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}

	}

	std::cout << "Current position is x: " << baseWidth << " y: " << baseDepth << " biome: " << biome->m_name << std::endl;
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
			unsigned int sampleBiomeLODs = BIOME_PERLIN_LODS;
			float sampleBiomeAmplitude = 1.0f;
			float sampleBiomeFrequency = 1.0f;
			float sampleNormFactorToAdd = PERLIN_NORM_FACTOR;
			float sampleNormFactor = 0.0f;
			float sampleTemperaturePerlinValue = 0.0f;
			float sampleHumidityPerlinValue = 0.0f;
			for (int i = 0; i < sampleBiomeLODs; i++) {
				sampleTemperaturePerlinValue += sampleBiomeAmplitude * m_temperaturePerlinGen.getValue(x * sampleBiomeFrequency, y * sampleBiomeFrequency);
				sampleHumidityPerlinValue += sampleBiomeAmplitude * m_humidityPerlinGen.getValue(x * sampleBiomeFrequency, y * sampleBiomeFrequency);
				sampleBiomeAmplitude = sampleBiomeAmplitude / 2.0f;
				sampleBiomeFrequency = sampleBiomeFrequency * 2.0f;
				sampleNormFactor += sampleNormFactorToAdd;
				sampleNormFactorToAdd = sampleNormFactorToAdd / 2.0f;
			}
			float sampleNormTPV = (sampleTemperaturePerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));
			float sampleNormMPV = (sampleHumidityPerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));

			if (sampleNormTPV < 0.0f) {
				sampleNormTPV = 0.0f;
			}
			if (sampleNormMPV < 0.0f) {
				sampleNormMPV = 0.0f;
			}
			if (sampleNormTPV > 1.0f) {
				sampleNormTPV = 1.0f;
			}
			if (sampleNormMPV > 1.0f) {
				sampleNormMPV = 1.0f;
			}
			Biome* sampleBiome = biomes[7];
			float sampleScaledHumidity = sampleNormMPV * sampleNormTPV;
			for (int i = 0; i < biomesCount; i++) {
				if (sampleNormTPV >= biomes[i]->m_minTemp && sampleNormTPV <= biomes[i]->m_maxTemp && sampleScaledHumidity >= biomes[i]->m_minHum && sampleScaledHumidity <= biomes[i]->m_maxHum) {
					sampleBiome = biomes[i];
					i = biomesCount;
				}
			}
			
			sampleHeights[k] = getBlockHeight(sampleBiome, x, y);
			std::cout << "Sample " << k << " x: " << x << " y: " << y << " biome: " << sampleBiome->m_name << " height: " << sampleHeights[k] << std::endl;
		}
		height = bilinearFilter(baseWidth, baseDepth, sampleHeights, sampleCoords);
		std::cout << "Bilinear filtering: " << height << std::endl;
		delete[] sampleHeights;
		delete[] sampleCoords;
	}
	else {
		std::cout << "No neighbours" << std::endl;
		height = getBlockHeight(biome, baseWidth, baseDepth);
	}

	delete[] neighbouringBiomes;
	std::cout << "Old Height " << height << " new height " << computeTerrainHeight(baseWidth, baseDepth, biome) << std::endl;
	return height;
}

float TerrainGenerator::computeTerrainHeight(float x, float y, Biome* &biome) {
	Biome** biomes = m_biomeManager->getBiomes();
	unsigned int biomesCount = m_biomeManager->getBiomesCount();
	Biome* currentBiome = biomes[7];
	Biome** neighbouringBiomes = new Biome * [(biomesCount - (size_t)1)];

	float temperaturePerlinValue = 0.0f;
	float humidityPerlinValue = 0.0f;
	unsigned int LODs = BIOME_PERLIN_LODS;
	float biomeFrequency = 1.0f;
	float biomeAmplitude = 1.0f;
	float normFactorToAdd = PERLIN_NORM_FACTOR;
	float normFactor = 0.0f;
	for (int i = 0; i < LODs; i++) {
		temperaturePerlinValue += biomeAmplitude * m_temperaturePerlinGen.getValue(x * biomeFrequency, y * biomeFrequency);
		humidityPerlinValue += biomeAmplitude * m_humidityPerlinGen.getValue(x * biomeFrequency, y * biomeFrequency);
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

	int neighbourBiomesCount = 0;
	float mainBiomeFactor = 0.0f;

	for (int i = 0; i < biomesCount; i++) {
		float minTempDelta = glm::abs(normTPV - biomes[i]->m_minTemp);
		float minHumDelta = glm::abs(scaledHumidity - biomes[i]->m_minHum);
		float maxTempDelta = glm::abs(normTPV - biomes[i]->m_maxTemp);
		float maxHumDelta = glm::abs(scaledHumidity - biomes[i]->m_maxHum);
		// could be problematic near zero
		if (normTPV >= biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp && scaledHumidity >= biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			currentBiome = biomes[i];
			biome = currentBiome;
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && scaledHumidity > biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxTempDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && scaledHumidity > biomes[i]->m_minHum && scaledHumidity <= biomes[i]->m_maxHum) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (minHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && normTPV > biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}
		else if (maxHumDelta <= BIOME_NEIGHBOUR_INFLUENCE_THRESHOLD && normTPV > biomes[i]->m_minTemp && normTPV <= biomes[i]->m_maxTemp) {
			neighbouringBiomes[neighbourBiomesCount++] = biomes[i];
		}

	}

	float height = 0.0f;
	if (neighbourBiomesCount > 0) {
		float* sampleHeights = new float[4];
		float* sampleCoords = new float[4];
		getBilinearSmoothingGridCoordinates(x, y, sampleCoords);

		float sampleX = 0.0f;
		float sampleY = 0.0f;
		for (int k = 0; k < 4; k++) {
			switch (k) {
			case 0:
				sampleX = sampleCoords[0];
				sampleY = sampleCoords[3];
				break;
			case 1:
				sampleX = sampleCoords[1];
				sampleY = sampleCoords[3];
				break;
			case 2:
				sampleX = sampleCoords[1];
				sampleY = sampleCoords[2];
				break;
			case 3:
				sampleX = sampleCoords[0];
				sampleY = sampleCoords[2];
				break;
			}
			unsigned int sampleBiomeLODs = BIOME_PERLIN_LODS;
			float sampleBiomeAmplitude = 1.0f;
			float sampleBiomeFrequency = 1.0f;
			float sampleNormFactorToAdd = PERLIN_NORM_FACTOR;
			float sampleNormFactor = 0.0f;
			float sampleTemperaturePerlinValue = 0.0f;
			float sampleHumidityPerlinValue = 0.0f;
			for (int i = 0; i < sampleBiomeLODs; i++) {
				sampleTemperaturePerlinValue += sampleBiomeAmplitude * m_temperaturePerlinGen.getValue(sampleX * sampleBiomeFrequency, sampleY * sampleBiomeFrequency);
				sampleHumidityPerlinValue += sampleBiomeAmplitude * m_humidityPerlinGen.getValue(sampleX * sampleBiomeFrequency, sampleY * sampleBiomeFrequency);
				sampleBiomeAmplitude = sampleBiomeAmplitude / 2.0f;
				sampleBiomeFrequency = sampleBiomeFrequency * 2.0f;
				sampleNormFactor += sampleNormFactorToAdd;
				sampleNormFactorToAdd = sampleNormFactorToAdd / 2.0f;
			}
			float sampleNormTPV = (sampleTemperaturePerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));
			float sampleNormMPV = (sampleHumidityPerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));

			if (sampleNormTPV < 0.0f) {
				sampleNormTPV = 0.0f;
			}
			if (sampleNormMPV < 0.0f) {
				sampleNormMPV = 0.0f;
			}
			if (sampleNormTPV > 1.0f) {
				sampleNormTPV = 1.0f;
			}
			if (sampleNormMPV > 1.0f) {
				sampleNormMPV = 1.0f;
			}
			Biome* sampleBiome = biomes[7];
			float sampleScaledHumidity = sampleNormMPV * sampleNormTPV;
			for (int i = 0; i < biomesCount; i++) {
				if (sampleNormTPV >= biomes[i]->m_minTemp && sampleNormTPV <= biomes[i]->m_maxTemp && sampleScaledHumidity >= biomes[i]->m_minHum && sampleScaledHumidity <= biomes[i]->m_maxHum) {
					sampleBiome = biomes[i];
					i = biomesCount;
				}
			}

			sampleHeights[k] = getBlockHeight(sampleBiome, sampleX, sampleY);
		}
		height = bilinearFilter(x, y, sampleHeights, sampleCoords);
		delete[] sampleHeights;
		delete[] sampleCoords;
	}
	else {
		height = getBlockHeight(currentBiome, x, y);
	}
	return height;
}

void TerrainGenerator::generateChunk(Block*** &blockMatrix, glm::vec3& chunkPosition) {
	Biome** biomes = m_biomeManager->getBiomes();
	unsigned int biomesCount = m_biomeManager->getBiomesCount();
	Biome* biome = biomes[7];
	for (int j = 0; j < m_chunkSideSize; j++) {
		for (int w = 0; w < m_chunkSideSize; w++) {
			float baseWidth = chunkPosition.x + ((j - (m_chunkSideSize / 2)) + 0.5f);
			float baseDepth = chunkPosition.z + ((w - (m_chunkSideSize / 2)) + 0.5f);
			float height = computeTerrainHeight(baseWidth, baseDepth, biome);
			int finalHeight = (int)height;
			int dirtHeight = 70;
			for (int i = 0; i < m_chunkHeight; i++) {
				BlockId blockId = BlockId::AIR;
				if (i <= finalHeight) {
					if (i < dirtHeight) {
						blockId = BlockId::STONE;
					}
					else if (i >= dirtHeight && i < finalHeight) {
						if (biome->m_biomeId == Biome::BiomeId::DESERT) {
							blockId = BlockId::SAND;
						}
						else {
							blockId = BlockId::DIRT;
						}
					}
					else if (i == finalHeight) {
						if (biome->m_biomeId == Biome::BiomeId::DESERT) {
							blockId = BlockId::SAND;
						}
						else if (biome->m_biomeId == Biome::BiomeId::TUNDRA) {
							blockId = BlockId::SNOWY_GRASS;
						}
						else {
							blockId = BlockId::GRASS;
						}
					}
				}
				blockMatrix[i][j][w].changeBlock(blockId);
				blockMatrix[i][j][w].setBiomeRef(biome);
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

void TerrainGenerator::decorateChunk(Block*** &blockMatrix, glm::vec3 &chunkPosition) {
	Biome** biomes = m_biomeManager->getBiomes();
	unsigned int biomesCount = m_biomeManager->getBiomesCount();
	float xMin = chunkPosition.x - (m_chunkSideSize / 2.0f);
	float xMax = chunkPosition.x + (m_chunkSideSize / 2.0f);
	float yMin = chunkPosition.z - (m_chunkSideSize / 2.0f);
	float yMax = chunkPosition.z + (m_chunkSideSize / 2.0f);

	unsigned int treeChunkSideSize = m_chunkSideSize + (m_treeChunkOffset * 2);
	float xTreeMin = chunkPosition.x - (treeChunkSideSize / 2.0f);
	float xTreeMax = chunkPosition.x + (treeChunkSideSize / 2.0f);
	float yTreeMin = chunkPosition.z - (treeChunkSideSize / 2.0f);
	float yTreeMax = chunkPosition.z + (treeChunkSideSize / 2.0f);
	Biome** relevantBiomes = new Biome*[biomesCount];
	for (int i = 0; i < biomesCount; i++) {
		relevantBiomes[i] = nullptr;
	}
	Biome*** treeChunkBiomeInfo = new Biome ** [treeChunkSideSize];
	for (int j = 0; j < treeChunkSideSize; j++) {
		treeChunkBiomeInfo[j] = new Biome * [treeChunkSideSize];
		for (int i = 0; i < treeChunkSideSize; i++) {
			treeChunkBiomeInfo[j][i] = nullptr;
		}
	}
	for (int j = 0; j < treeChunkSideSize; j++) {
		for (int w = 0; w < treeChunkSideSize; w++) {
			float x = chunkPosition.x + ((j - (treeChunkSideSize / 2.0f)) + 0.5f);
			float y = chunkPosition.z + ((w - (treeChunkSideSize / 2.0f)) + 0.5f);
			unsigned int sampleBiomeLODs = BIOME_PERLIN_LODS;
			float sampleBiomeAmplitude = 1.0f;
			float sampleBiomeFrequency = 1.0f;
			float sampleNormFactorToAdd = PERLIN_NORM_FACTOR;
			float sampleNormFactor = 0.0f;
			float sampleTemperaturePerlinValue = 0.0f;
			float sampleHumidityPerlinValue = 0.0f;
			for (int i = 0; i < sampleBiomeLODs; i++) {
				sampleTemperaturePerlinValue += sampleBiomeAmplitude * m_temperaturePerlinGen.getValue(x * sampleBiomeFrequency, y * sampleBiomeFrequency);
				sampleHumidityPerlinValue += sampleBiomeAmplitude * m_humidityPerlinGen.getValue(x * sampleBiomeFrequency, y * sampleBiomeFrequency);
				sampleBiomeAmplitude = sampleBiomeAmplitude / 2.0f;
				sampleBiomeFrequency = sampleBiomeFrequency * 2.0f;
				sampleNormFactor += sampleNormFactorToAdd;
				sampleNormFactorToAdd = sampleNormFactorToAdd / 2.0f;
			}
			float sampleNormTPV = (sampleTemperaturePerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));
			float sampleNormMPV = (sampleHumidityPerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));

			if (sampleNormTPV < 0.0f) {
				sampleNormTPV = 0.0f;
			}
			if (sampleNormMPV < 0.0f) {
				sampleNormMPV = 0.0f;
			}
			if (sampleNormTPV > 1.0f) {
				sampleNormTPV = 1.0f;
			}
			if (sampleNormMPV > 1.0f) {
				sampleNormMPV = 1.0f;
			}
			Biome* sampleBiome = biomes[7];
			float sampleScaledHumidity = sampleNormMPV * sampleNormTPV;
			for (int i = 0; i < biomesCount; i++) {
				if (sampleNormTPV >= biomes[i]->m_minTemp && sampleNormTPV <= biomes[i]->m_maxTemp && sampleScaledHumidity >= biomes[i]->m_minHum && sampleScaledHumidity <= biomes[i]->m_maxHum) {
					sampleBiome = biomes[i];
					i = biomesCount;
				}
			}
			treeChunkBiomeInfo[j][w] = sampleBiome;
			for (int i = 0; i < biomesCount; i++) {
				if (relevantBiomes[i] != nullptr) {
					if (relevantBiomes[i]->m_biomeId == sampleBiome->m_biomeId) {
						i = biomesCount;
					}
				}
				else {
					relevantBiomes[i] = sampleBiome;
					i = biomesCount;
				}
			}
		}
	}
	for (int i = 0; i < biomesCount; i++) {
		if (relevantBiomes[i] != nullptr) {
			Biome* biome = relevantBiomes[i];
			std::vector<std::pair<float, float>> trees;
			computeAreaTreeList(chunkPosition.x, chunkPosition.z, treeChunkSideSize, trees, biome);
			for (std::pair<float, float>& tree : trees) {
				unsigned int sampleBiomeLODs = BIOME_PERLIN_LODS;
				float sampleBiomeAmplitude = 1.0f;
				float sampleBiomeFrequency = 1.0f;
				float sampleNormFactorToAdd = PERLIN_NORM_FACTOR;
				float sampleNormFactor = 0.0f;
				float sampleTemperaturePerlinValue = 0.0f;
				float sampleHumidityPerlinValue = 0.0f;
				float cubeCenterX = 0.0f;
				float cubeCenterZ = 0.0f;
				if (tree.first <= 0.0f) {
					cubeCenterX = int(tree.first) - 0.5f;
				}
				else {
					cubeCenterX = int(tree.first) + 0.5f;
				}
				if (tree.second <= 0.0f) {
					cubeCenterZ = int(tree.second) - 0.5f;
				}
				else {
					cubeCenterZ = int(tree.second) + 0.5f;
				}
				for (int k = 0; k < sampleBiomeLODs; k++) {
					sampleTemperaturePerlinValue += sampleBiomeAmplitude * m_temperaturePerlinGen.getValue(cubeCenterX * sampleBiomeFrequency, cubeCenterZ * sampleBiomeFrequency);
					sampleHumidityPerlinValue += sampleBiomeAmplitude * m_humidityPerlinGen.getValue(cubeCenterX * sampleBiomeFrequency, cubeCenterZ * sampleBiomeFrequency);
					sampleBiomeAmplitude = sampleBiomeAmplitude / 2.0f;
					sampleBiomeFrequency = sampleBiomeFrequency * 2.0f;
					sampleNormFactor += sampleNormFactorToAdd;
					sampleNormFactorToAdd = sampleNormFactorToAdd / 2.0f;
				}
				float sampleNormTPV = (sampleTemperaturePerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));
				float sampleNormMPV = (sampleHumidityPerlinValue - (-sampleNormFactor)) / (sampleNormFactor - (-sampleNormFactor));

				if (sampleNormTPV < 0.0f) {
					sampleNormTPV = 0.0f;
				}
				if (sampleNormMPV < 0.0f) {
					sampleNormMPV = 0.0f;
				}
				if (sampleNormTPV > 1.0f) {
					sampleNormTPV = 1.0f;
				}
				if (sampleNormMPV > 1.0f) {
					sampleNormMPV = 1.0f;
				}
				Biome* sampleBiome = biomes[7];
				float sampleScaledHumidity = sampleNormMPV * sampleNormTPV;
				for (int i = 0; i < biomesCount; i++) {
					if (sampleNormTPV >= biomes[i]->m_minTemp && sampleNormTPV <= biomes[i]->m_maxTemp && sampleScaledHumidity >= biomes[i]->m_minHum && sampleScaledHumidity <= biomes[i]->m_maxHum) {
						sampleBiome = biomes[i];
						i = biomesCount;
					}
				}
				if (sampleBiome->m_biomeId == biome->m_biomeId) {
					float height = computeTerrainHeight(cubeCenterX, cubeCenterZ, sampleBiome);
					float cubeCenterY = ((int)height) + 0.5f;
					switch (sampleBiome->m_biomeId) {
					case Biome::BiomeId::FOREST:
						m_treeBuilder->buildForestTree(cubeCenterY, cubeCenterX, cubeCenterZ, chunkPosition.x, chunkPosition.z, m_chunkSideSize, xTreeMin, yTreeMin, blockMatrix);
						break;
					}
				}
			}
		}
		else {
			i = biomesCount;
		}
	}
	

	delete[] relevantBiomes;
	for (int j = 0; j < treeChunkSideSize; j++) {
		delete[] treeChunkBiomeInfo[j];
	}
}

void TerrainGenerator::computeAreaTreeList(float chunkX, float chunkY, unsigned int treeChunkSideSize, std::vector<std::pair<float, float>>& trees, Biome* biome) {

	float xMin = chunkX - (treeChunkSideSize / 2.0f);
	float xMax = chunkX + (treeChunkSideSize / 2.0f);
	float yMin = chunkY - (treeChunkSideSize / 2.0f);
	float yMax = chunkY + (treeChunkSideSize / 2.0f);

	if (biome->m_hasTrees) {
		unsigned int cellSideSize = 0;
		float gridXMin = 0.0f;
		float gridXMax = 0.0f;
		float gridYMin = 0.0f;
		float gridYMax = 0.0f;
		if (dynamic_cast<ForestBiome*>(biome) != nullptr) {
			ForestBiome* forestBiome = dynamic_cast<ForestBiome*>(biome);
			cellSideSize = forestBiome->m_treeGridCellSide;
			float treeGridSideSize = 0;
			int gridMinXIndex = int(xMin / (float)cellSideSize);
			gridMinXIndex--;
			int gridMinYIndex = int(yMin / (float)cellSideSize);
			gridMinYIndex--;
			gridXMin = gridMinXIndex * (float)cellSideSize;
			gridYMin = gridMinYIndex * (float)cellSideSize;
			treeGridSideSize = (int((chunkX - gridXMin) / (float)cellSideSize) + 1) * 2;
			gridXMax = gridXMin + treeGridSideSize;
			gridYMax = gridYMin + treeGridSideSize;
			for (int i = 0; i < treeGridSideSize; i++) {
				for (int j = 0; j < treeGridSideSize; j++) {
					float perlinNormFactor = 0.45f;
					// The last term, 0.25f is added so that the cell center doesn't happen to be at a perlin grid corner
					float cellCenterX = gridXMin + (i * cellSideSize) + (cellSideSize / 2.0f) + 0.25f;
					float cellCenterY = gridYMin + (j * cellSideSize) + (cellSideSize / 2.0f) + 0.25f;
					float xOffsetNoiseSample = forestBiome->m_treesXPerlinGen.getValue(cellCenterX, cellCenterY);
					float yOffsetNoiseSample = forestBiome->m_treesYPerlinGen.getValue(cellCenterX, cellCenterY);
					float xOffsetNorm = ((xOffsetNoiseSample - (-perlinNormFactor)) / (perlinNormFactor - (-perlinNormFactor)) * 2.0f) - 1;
					float yOffsetNorm = ((yOffsetNoiseSample - (-perlinNormFactor)) / (perlinNormFactor - (-perlinNormFactor)) * 2.0f) - 1;
					if (xOffsetNorm < -1.0f) {
						xOffsetNorm = -1.0f;
					}
					if (yOffsetNorm < -1.0f) {
						yOffsetNorm = -1.0f;
					}
					if (xOffsetNorm > 1.0f) {
						xOffsetNorm = 1.0f;
					}
					if (yOffsetNorm > 1.0f) {
						yOffsetNorm = 1.0f;
					}
					float xOffsetScaled = xOffsetNorm * ((cellSideSize / 2.0f) - (cellSideSize / 8.0f));
					float yOffsetScaled = yOffsetNorm * ((cellSideSize / 2.0f) - (cellSideSize / 8.0f));
					float treeX = cellCenterX + xOffsetScaled;
					float treeY = cellCenterY + yOffsetScaled;
					trees.push_back(std::pair<float, float>(treeX, treeY));
				}
			}
		}
	}
}