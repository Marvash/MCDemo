#pragma once

#include "coreInclude.h"

class PerlinNoiseGenerator {
public:
	PerlinNoiseGenerator();
	float getValue(float x, float y, int period, float amplitude);
private:
	const unsigned int seed = 123456;

	unsigned int northSeed;
	unsigned int eastSeed;
	unsigned int southSeed;
	unsigned int westSeed;

	std::ranlux48_base northRandomEngine;
	std::ranlux48_base eastRandomEngine;
	std::ranlux48_base southRandomEngine;
	std::ranlux48_base westRandomEngine;

	void resetEngines();
	glm::vec2 getConstantVector(unsigned long long number);
	float fadeFunc(float val);
	float scalarLerp(float a, float b, float factor);
};

