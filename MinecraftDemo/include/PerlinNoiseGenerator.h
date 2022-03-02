#pragma once

#include "coreInclude.h"
#include <boost/random/ranlux.hpp>

class PerlinNoiseGenerator {
public:

	bool generatorsShouldStop;

	PerlinNoiseGenerator();
	PerlinNoiseGenerator(const PerlinNoiseGenerator& other);
	float getValue(float x, float y);
	void startGeneratorThreads();
	void updatePlayerOffset(float newOffsetX, float newOffsetY);

	PerlinNoiseGenerator& operator=(PerlinNoiseGenerator other);

	void setSeed(unsigned long long newSeed);
	unsigned long long getSeed();
	void setPeriod(unsigned long newPeriod);
	unsigned long getPeriod();
private:

	unsigned long long seed;
	unsigned long period;

	unsigned long long northSeed;
	unsigned long long eastSeed;
	unsigned long long southSeed;
	unsigned long long westSeed;

	bool cacheEnabled = true;
	bool cacheInit = false;

	static const int nWorkersGens;
	static const int cacheSize;

	boost::thread_group generatorThreads;
	boost::mutex internalLockLP;
	boost::mutex internalLockNext;
	boost::mutex internalLockData;

	unsigned long long** cacheNorth;
	unsigned long long** cacheSouth;
	unsigned long long** cacheWest;
	unsigned long long** cacheEast;

	float playerOffsetX;
	float playerOffsetY;

	glm::vec2 getConstantVector(unsigned long long number);
	float fadeFunc(float val);
	float scalarLerp(float a, float b, float factor);
	void generatorThreadLoop();
	void cacheValue();
	void initCache();

	void lockHP();
	void unlockHP();
	void lockLP();
	void unlockLP();
};

