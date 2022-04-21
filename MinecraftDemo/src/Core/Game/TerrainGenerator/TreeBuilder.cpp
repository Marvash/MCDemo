#include "TreeBuilder.h"

TreeBuilder::TreeBuilder() {

}

void TreeBuilder::buildForestTree(float treeY, float treeX, float treeZ, float chunkX, float chunkY, unsigned int chunkSideSize, float xTreeMin, float yTreeMin, Cube***& blockMatrix) {
	float xChunkMin = chunkX - (chunkSideSize / 2.0f);
	float yChunkMin = chunkY - (chunkSideSize / 2.0f);
	float xChunkMax = chunkX + (chunkSideSize / 2.0f);
	float yChunkMax = chunkY + (chunkSideSize / 2.0f);

	float relativeTreeX = 0.0f;
	float relativeTreeZ = 0.0f;
	float relativeTreeY = 0.0f;

	float tmpTreeX = 0.0f;
	float tmpTreeZ = 0.0f;

	int treeWidth = 2;

	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	for (int i = -treeWidth; i <= treeWidth; i++) {
		for (int j = -treeWidth; j <= treeWidth; j++) {
			tmpTreeX = treeX + i;
			tmpTreeZ = treeZ + j;
			if (tmpTreeX > xChunkMin && tmpTreeX < xChunkMax && tmpTreeZ > yChunkMin && tmpTreeZ < yChunkMax) {
				relativeTreeX = tmpTreeX - xChunkMin;
				relativeTreeZ = tmpTreeZ - yChunkMin;
				relativeTreeY = treeY;
				if (blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].getCubeId() == Cube::CubeId::AIR_BLOCK) {
					blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::LEAVES);
				}
			}
		}
	}
	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	for (int i = -treeWidth; i <= treeWidth; i++) {
		for (int j = -treeWidth; j <= treeWidth; j++) {
			tmpTreeX = treeX + i;
			tmpTreeZ = treeZ + j;
			if (tmpTreeX > xChunkMin && tmpTreeX < xChunkMax && tmpTreeZ > yChunkMin && tmpTreeZ < yChunkMax) {
				relativeTreeX = tmpTreeX - xChunkMin;
				relativeTreeZ = tmpTreeZ - yChunkMin;
				relativeTreeY = treeY;
				if (blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].getCubeId() == Cube::CubeId::AIR_BLOCK) {
					blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::LEAVES);
				}
			}
		}
	}
	treeY += 1.0f;
	if (treeX > xChunkMin && treeX < xChunkMax && treeZ > yChunkMin && treeZ < yChunkMax) {
		relativeTreeX = treeX - xChunkMin;
		relativeTreeZ = treeZ - yChunkMin;
		relativeTreeY = treeY;
		blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::OAK_LOG);
	}
	for (int i = -treeWidth; i <= treeWidth; i++) {
		for (int j = -treeWidth; j <= treeWidth; j++) {
			tmpTreeX = treeX + i;
			tmpTreeZ = treeZ + j;
			if (tmpTreeX > xChunkMin && tmpTreeX < xChunkMax && tmpTreeZ > yChunkMin && tmpTreeZ < yChunkMax) {
				relativeTreeX = tmpTreeX - xChunkMin;
				relativeTreeZ = tmpTreeZ - yChunkMin;
				relativeTreeY = treeY;
				if (blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].getCubeId() == Cube::CubeId::AIR_BLOCK) {
					blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::LEAVES);
				}
			}
		}
	}
	treeY += 1.0f;
	for (int i = -treeWidth; i <= treeWidth; i++) {
		for (int j = -treeWidth; j <= treeWidth; j++) {
			tmpTreeX = treeX + i;
			tmpTreeZ = treeZ + j;
			if (tmpTreeX > xChunkMin && tmpTreeX < xChunkMax && tmpTreeZ > yChunkMin && tmpTreeZ < yChunkMax) {
				relativeTreeX = tmpTreeX - xChunkMin;
				relativeTreeZ = tmpTreeZ - yChunkMin;
				relativeTreeY = treeY;
				if (blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].getCubeId() == Cube::CubeId::AIR_BLOCK) {
					blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::LEAVES);
				}
			}
		}
	}
	treeY += 1.0f;
	for (int i = -treeWidth; i <= treeWidth; i++) {
		for (int j = -treeWidth; j <= treeWidth; j++) {
			tmpTreeX = treeX + i;
			tmpTreeZ = treeZ + j;
			if (tmpTreeX > xChunkMin && tmpTreeX < xChunkMax && tmpTreeZ > yChunkMin && tmpTreeZ < yChunkMax) {
				relativeTreeX = tmpTreeX - xChunkMin;
				relativeTreeZ = tmpTreeZ - yChunkMin;
				relativeTreeY = treeY;
				if (blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].getCubeId() == Cube::CubeId::AIR_BLOCK) {
					blockMatrix[int(relativeTreeY)][int(relativeTreeX)][int(relativeTreeZ)].setCubeId(Cube::CubeId::LEAVES);
				}
			}
		}
	}
}
