#include "PerlinNoiseGenerator.h"

const int PerlinNoiseGenerator::nWorkersGens = 2;
const int PerlinNoiseGenerator::cacheSize = 1024;

PerlinNoiseGenerator::PerlinNoiseGenerator() : period(1) {
	boost::ranlux3 randomEngine;
	randomEngine.seed(std::time(0));
	northSeed = randomEngine();
	eastSeed = northSeed + 1;
	southSeed = northSeed + 2;
	westSeed = northSeed + 3;
}

PerlinNoiseGenerator::PerlinNoiseGenerator(const PerlinNoiseGenerator& other) {
	northSeed = other.northSeed;
	eastSeed = other.eastSeed;
	southSeed = other.southSeed;
	westSeed = other.westSeed;
}

PerlinNoiseGenerator& PerlinNoiseGenerator::operator=(PerlinNoiseGenerator other) {
	northSeed = other.northSeed;
	eastSeed = other.eastSeed;
	southSeed = other.southSeed;
	westSeed = other.westSeed;
	return *this;
}

void PerlinNoiseGenerator::setSeed(unsigned long long newSeed) {
	seed = newSeed;
	northSeed = seed;
	eastSeed = northSeed + 1;
	southSeed = northSeed + 2;
	westSeed = northSeed + 3;
}

unsigned long long PerlinNoiseGenerator::getSeed() {
	return seed;
}

void PerlinNoiseGenerator::setPeriod(unsigned long newPeriod) {
	period = newPeriod;
}

unsigned long PerlinNoiseGenerator::getPeriod() {
	return period;
}

void PerlinNoiseGenerator::updatePlayerOffset(float newOffsetX, float newOffsetY) {
	lockHP();
	playerOffsetX = newOffsetX;
	playerOffsetY = newOffsetY;
	unlockHP();
}

void PerlinNoiseGenerator::startGeneratorThreads() {
	for (int i = 0; i < nWorkersGens; i++) {
		generatorThreads.create_thread(boost::bind(&PerlinNoiseGenerator::generatorThreadLoop, this));
	}
}

void PerlinNoiseGenerator::generatorThreadLoop() {
	while (!generatorsShouldStop) {
		cacheValue();
	}
}

void PerlinNoiseGenerator::initCache() {
	cacheNorth = new unsigned long long* [cacheSize];
	for (int i = 0; i < cacheSize; i++) {
		cacheNorth[i] = new unsigned long long(0);
	}
	cacheSouth = new unsigned long long* [cacheSize];
	for (int i = 0; i < cacheSize; i++) {
		cacheSouth[i] = new unsigned long long(0);
	}
	cacheWest = new unsigned long long* [cacheSize];
	for (int i = 0; i < cacheSize; i++) {
		cacheWest[i] = new unsigned long long(0);
	}
	cacheEast = new unsigned long long* [cacheSize];
	for (int i = 0; i < cacheSize; i++) {
		cacheEast[i] = new unsigned long long(0);
	}
	cacheInit = true;
}

void PerlinNoiseGenerator::cacheValue() {
	if (!cacheInit)
		initCache();

	lockLP();
	for (int i = 0; i < cacheSize; i++) {
		if (cacheNorth[i] == nullptr) {
			int coordY = i + playerOffsetY;
			std::ranlux48_base northRandomEngine;
		}
	}
	unlockLP();

	/*
	for (int i = 0; i < cacheSize; i++) {
		for (int j = 0; j < cacheSize; j++) {
			lockLP();
			
			if (cache[i][j] = nullptr) {
				
				std::ranlux48_base eastRandomEngine;
				std::ranlux48_base southRandomEngine;
				std::ranlux48_base westRandomEngine;

				northRandomEngine.seed(northSeed);
				eastRandomEngine.seed(eastSeed);
				southRandomEngine.seed(southSeed);
				westRandomEngine.seed(westSeed);

				unsigned long long topLeftValue = 0;
				unsigned long long topRightValue = 0;
				unsigned long long bottomLeftValue = 0;
				unsigned long long bottomRightValue = 0;
				unsigned long long tmpVal = 0;

				int xOffset = (((int)x) / period) * period;
				int yOffset = (((int)y) / period) * period;
				float xf, yf;
				if (x <= 0.0f) {
					xf = glm::abs(x - (xOffset - period));
				}
				else {
					xf = glm::abs(x - xOffset);
				}
				if (y <= 0.0f) {
					yf = glm::abs(y - yOffset);
				}
				else {
					yf = glm::abs(y - (yOffset + period));
				}

				if (yOffset == 0) {
					if (y > 0.0f) {
						tmpVal = southRandomEngine() / 2;
						topLeftValue += tmpVal;
						topRightValue += tmpVal;
						southRandomEngine.discard(period - 2);
						tmpVal = southRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						bottomRightValue += tmpVal;
					}
					else {
						tmpVal = southRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						bottomRightValue += tmpVal;
						northRandomEngine.discard(period - 1);
						tmpVal = northRandomEngine() / 2;
						topLeftValue += tmpVal;
						topRightValue += tmpVal;
					}
				}
				else {
					if (y > 0.0f) {
						southRandomEngine.discard(yOffset - 1);
						tmpVal = southRandomEngine() / 2;
						topLeftValue += tmpVal;
						topRightValue += tmpVal;
						southRandomEngine.discard(period - 1);
						tmpVal = southRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						bottomRightValue += tmpVal;
					}
					else {
						northRandomEngine.discard(glm::abs(yOffset) - 1);
						tmpVal = northRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						bottomRightValue += tmpVal;
						northRandomEngine.discard(period - 1);
						tmpVal = northRandomEngine() / 2;
						topLeftValue += tmpVal;
						topRightValue += tmpVal;
					}
				}
				if (xOffset == 0) {
					if (x > 0.0f) {
						tmpVal = eastRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						topLeftValue += tmpVal;
						eastRandomEngine.discard(period - 2);
						tmpVal = eastRandomEngine() / 2;
						bottomRightValue += tmpVal;
						topRightValue += tmpVal;
					}
					else {
						tmpVal = eastRandomEngine() / 2;
						bottomRightValue += tmpVal;
						topRightValue += tmpVal;
						westRandomEngine.discard(period - 1);
						tmpVal = westRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						topLeftValue += tmpVal;
					}
				}
				else {
					if (x > 0.0f) {
						eastRandomEngine.discard(xOffset - 1);
						tmpVal = eastRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						topLeftValue += tmpVal;
						eastRandomEngine.discard(period - 1);
						tmpVal = eastRandomEngine() / 2;
						bottomRightValue += tmpVal;
						topRightValue += tmpVal;
					}
					else {
						westRandomEngine.discard(glm::abs(xOffset) - 1);
						tmpVal = westRandomEngine() / 2;
						bottomRightValue += tmpVal;
						topRightValue += tmpVal;
						westRandomEngine.discard(period - 1);
						tmpVal = westRandomEngine() / 2;
						bottomLeftValue += tmpVal;
						topLeftValue += tmpVal;
					}
				}
			}
			unlockLP();
		}
	}
	*/
}

float PerlinNoiseGenerator::getValue(float x, float y) {

	boost::ranlux3 northRandomEngine;
	boost::ranlux3 eastRandomEngine;
	boost::ranlux3 southRandomEngine;
	boost::ranlux3 westRandomEngine;

	northRandomEngine.seed(northSeed);
	eastRandomEngine.seed(eastSeed);
	southRandomEngine.seed(southSeed);
	westRandomEngine.seed(westSeed);

	unsigned long long topLeftValue = 0;
	unsigned long long topRightValue = 0;
	unsigned long long bottomLeftValue = 0;
	unsigned long long bottomRightValue = 0;
	unsigned long long tmpVal = 0;

	long castPeriod = (long)period;

	long xOffset = (((long)x) / castPeriod) * castPeriod;
	long yOffset = (((long)y) / castPeriod) * castPeriod;
	long xJumps = glm::abs((((long)x) / castPeriod));
	long yJumps = glm::abs((((long)y) / castPeriod));
	float xf, yf;
	if (x <= 0.0f) {
		xf = glm::abs((float)(xOffset - castPeriod) - x) / (float)castPeriod;
	}
	else {
		xf = glm::abs(x - (float)xOffset) / (float)castPeriod;
	}

	if (y <= 0.0f) {
		yf = glm::abs(y - (float)yOffset) / (float)castPeriod;
	}
	else {
		yf = glm::abs((float)(yOffset + castPeriod) - y) / (float)castPeriod;
	}

	if (yOffset == 0) {
		if (y > 0.0f) {
			tmpVal = southRandomEngine();
			topLeftValue += tmpVal;
			topRightValue += tmpVal;
			tmpVal = southRandomEngine();
			bottomLeftValue += tmpVal;
			bottomRightValue += tmpVal;
		}
		else {
			tmpVal = southRandomEngine();
			bottomLeftValue += tmpVal;
			bottomRightValue += tmpVal;
			tmpVal = northRandomEngine();
			topLeftValue += tmpVal;
			topRightValue += tmpVal;
		}
	}
	else {
		if (y > 0.0f) {
			southRandomEngine.discard(yJumps);
			tmpVal = southRandomEngine();
			topLeftValue += tmpVal;
			topRightValue += tmpVal;
			tmpVal = southRandomEngine();
			bottomLeftValue += tmpVal;
			bottomRightValue += tmpVal;
		}
		else {
			northRandomEngine.discard(yJumps - 1);
			tmpVal = northRandomEngine();
			bottomLeftValue += tmpVal;
			bottomRightValue += tmpVal;
			tmpVal = northRandomEngine();
			topLeftValue += tmpVal;
			topRightValue += tmpVal;
		}
	}
	if (xOffset == 0) {
		if (x > 0.0f) {
			tmpVal = eastRandomEngine();
			bottomLeftValue += tmpVal;
			topLeftValue += tmpVal;
			tmpVal = eastRandomEngine();
			bottomRightValue += tmpVal;
			topRightValue += tmpVal;
		}
		else {
			tmpVal = eastRandomEngine();
			bottomRightValue += tmpVal;
			topRightValue += tmpVal;
			tmpVal = westRandomEngine();
			bottomLeftValue += tmpVal;
			topLeftValue += tmpVal;
		}
	}
	else {
		if (x > 0.0f) {
			eastRandomEngine.discard(xJumps);
			tmpVal = eastRandomEngine();
			bottomLeftValue += tmpVal;
			topLeftValue += tmpVal;
			tmpVal = eastRandomEngine();
			bottomRightValue += tmpVal;
			topRightValue += tmpVal;
		}
		else {
			westRandomEngine.discard(xJumps - 1);
			tmpVal = westRandomEngine();
			bottomRightValue += tmpVal;
			topRightValue += tmpVal;
			tmpVal = westRandomEngine();
			bottomLeftValue += tmpVal;
			topLeftValue += tmpVal;
		}
	}

	glm::vec2 topLeftVector = glm::vec2(xf, yf - 1.0f);
	glm::vec2 topRightVector = glm::vec2(xf - 1.0f, yf - 1.0f);
	glm::vec2 bottomLeftVector = glm::vec2(xf, yf);
	glm::vec2 bottomRightVector = glm::vec2(xf - 1.0f, yf);

	float dotTopLeft = glm::dot(topLeftVector, getConstantVector(topLeftValue));
	float dotTopRight = glm::dot(topRightVector, getConstantVector(topRightValue));
	float dotBottomLeft = glm::dot(bottomLeftVector, getConstantVector(bottomLeftValue));
	float dotBottomRight = glm::dot(bottomRightVector, getConstantVector(bottomRightValue));

	float u = fadeFunc(xf);
	float v = fadeFunc(yf);

	float result = scalarLerp(scalarLerp(dotBottomLeft, dotTopLeft, v), scalarLerp(dotBottomRight, dotTopRight, v), u);

	return result;
}

glm::vec2 PerlinNoiseGenerator::getConstantVector(unsigned long long number) {
	unsigned long long vecIndex = number % 4;
	switch (vecIndex) {
	case 0:
		return glm::vec2(1.0f, 1.0f);
	case 1:
		return glm::vec2(-1.0f, 1.0f);
	case 2:
		return glm::vec2(-1.0f, -1.0f);
	default:
		return glm::vec2(1.0f, -1.0f);
	}
}

float PerlinNoiseGenerator::fadeFunc(float val) {
	return ((6 * val - 15) * val + 10) * val * val * val;
}

float PerlinNoiseGenerator::scalarLerp(float a, float b, float factor) {
	return a + factor * (b - a);
}

void PerlinNoiseGenerator::lockHP() {
	internalLockNext.lock();
	internalLockData.lock();
	internalLockNext.unlock();
}
void PerlinNoiseGenerator::unlockHP() {
	internalLockData.unlock();
}
void PerlinNoiseGenerator::lockLP() {
	internalLockLP.lock();
	internalLockNext.lock();
	internalLockData.lock();
	internalLockNext.unlock();
}
void PerlinNoiseGenerator::unlockLP() {
	internalLockData.unlock();
	internalLockLP.unlock();
}