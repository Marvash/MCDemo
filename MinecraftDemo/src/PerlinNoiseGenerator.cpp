#include "PerlinNoiseGenerator.h"

PerlinNoiseGenerator::PerlinNoiseGenerator() {

	northSeed = seed;
	eastSeed = seed + 1;
	southSeed = seed + 2;
	westSeed = seed + 3;
}

float PerlinNoiseGenerator::getValue(float x, float y, int period, float amplitude) {

	std::ranlux48_base northRandomEngine;
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
	if (x < 0.0f) {
		xf = glm::abs(x - (xOffset - period));
	}
	else {
		xf = glm::abs(x - xOffset);
	}
	if (y < 0.0f) {
		yf = glm::abs(y - yOffset);
	}
	else {
		yf = glm::abs(y - (yOffset + period));
	}
	glm::vec2 diffVector(xf, yf);
	//if ((x == 0.5f || x == -0.5f) && y == -10.5f)
		//std::cout << "XXXXXX " << x << " " << y << " " << xOffset << " " << yOffset << " " << xf << " " << yf << std::endl;
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
	
	glm::vec2 topLeftVector = glm::vec2(xf, yf - period) / (float)period;
	glm::vec2 topRightVector = glm::vec2(xf - period, yf - period) / (float)period;
	glm::vec2 bottomLeftVector = glm::vec2(xf, yf) / (float)period;
	glm::vec2 bottomRightVector = glm::vec2(xf - period, yf) / (float)period;

	float dotTopLeft = glm::dot(topLeftVector, getConstantVector(topLeftValue));
	float dotTopRight = glm::dot(topRightVector, getConstantVector(topRightValue));
	float dotBottomLeft = glm::dot(bottomLeftVector, getConstantVector(bottomLeftValue));
	float dotBottomRight = glm::dot(bottomRightVector, getConstantVector(bottomRightValue));
	
	float u = fadeFunc(xf / period);
	float v = fadeFunc(yf / period);

	float result = amplitude * scalarLerp(scalarLerp(dotTopRight, dotBottomRight, v), scalarLerp(dotTopLeft, dotBottomLeft, v), u);

	return result;
}

glm::vec2 PerlinNoiseGenerator::getConstantVector(unsigned long long number) {
	unsigned long long vecIndex = number % 3;
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
	return factor * a + (1 - factor) * b;
}
