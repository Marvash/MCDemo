#include "Cube.h"

float* Cube::grassBlockTexCoords;
float* Cube::grassBlockTexColors;

Cube::Cube() {

}

Cube::Cube(CubeId cubeId) : cubeId(cubeId) {

}

std::string Cube::getDisplayName(CubeId cubeId) {

}

int Cube::getNumericId(CubeId cubeId) {

}

float* Cube::getAtlasTexCoords(CubeId cubeId, FaceSide faceSide) {
	float* texCoords = nullptr;
	switch (cubeId) {
	case CubeId::GRASS_BLOCK:
		switch (faceSide) {
		case FaceSide::RIGHT:
		case FaceSide::LEFT:
		case FaceSide::FRONT:
		case FaceSide::BACK:
			return &grassBlockTexCoords[0];
		case FaceSide::TOP:
			return &grassBlockTexCoords[16];
		case FaceSide::BOTTOM:
			return &grassBlockTexCoords[32];
		}
		break;
	}
	return texCoords;
}
float* Cube::getTexColor(CubeId cubeId, FaceSide faceSide) {
	float* colors = nullptr;
	switch (cubeId) {
	case CubeId::GRASS_BLOCK:
		glm::vec3 grassColor = glm::pow(glm::vec3(0.474f, 0.752f, 0.352f), glm::vec3(2.2));
		switch (faceSide) {
		case FaceSide::RIGHT:
		case FaceSide::LEFT:
		case FaceSide::FRONT:
		case FaceSide::BACK:
			colors = &grassBlockTexColors[0];
			break;
		case FaceSide::TOP:
			colors = &grassBlockTexColors[6];
			break;
		case FaceSide::BOTTOM:
			colors = &grassBlockTexColors[12];
			break;
		}
		break;
	}
	
	return colors;
}

Cube::CubeId Cube::getCubeId() {
	return cubeId;
}

void Cube::setCubeId(Cube::CubeId cubeId) {
	this->cubeId = cubeId;
}


void Cube::init() {
	AtlasManager* mainAltas = AtlasManager::instance();
	grassBlockTexCoords = new float[48];
	// SIDE
	grassBlockTexCoords[0] = mainAltas->getCoordX(12) + mainAltas->textureOffset;
	grassBlockTexCoords[1] = mainAltas->getCoordY(10) - mainAltas->textureOffset;
	grassBlockTexCoords[2] = mainAltas->getCoordX(13) + mainAltas->textureOffset;
	grassBlockTexCoords[3] = grassBlockTexCoords[1];
	grassBlockTexCoords[4] = mainAltas->getCoordX(13) - mainAltas->textureOffset;
	grassBlockTexCoords[5] = grassBlockTexCoords[1];
	grassBlockTexCoords[6] = mainAltas->getCoordX(14) - mainAltas->textureOffset;
	grassBlockTexCoords[7] = grassBlockTexCoords[1];
	grassBlockTexCoords[8] = grassBlockTexCoords[4];
	grassBlockTexCoords[9] = mainAltas->getCoordY(11) + mainAltas->textureOffset;
	grassBlockTexCoords[10] = grassBlockTexCoords[6];
	grassBlockTexCoords[11] = grassBlockTexCoords[9];
	grassBlockTexCoords[12] = grassBlockTexCoords[0];
	grassBlockTexCoords[13] = grassBlockTexCoords[9];
	grassBlockTexCoords[14] = grassBlockTexCoords[2];
	grassBlockTexCoords[15] = grassBlockTexCoords[9];
	// TOP
	grassBlockTexCoords[16] = mainAltas->getCoordX(15) + mainAltas->textureOffset;
	grassBlockTexCoords[17] = grassBlockTexCoords[1];
	grassBlockTexCoords[18] = -1.0f;
	grassBlockTexCoords[19] = -1.0f;
	grassBlockTexCoords[20] = mainAltas->getCoordX(16) - mainAltas->textureOffset;
	grassBlockTexCoords[21] = grassBlockTexCoords[1];
	grassBlockTexCoords[22] = -1.0f;
	grassBlockTexCoords[23] = -1.0f;
	grassBlockTexCoords[24] = grassBlockTexCoords[20];
	grassBlockTexCoords[25] = grassBlockTexCoords[9];
	grassBlockTexCoords[26] = -1.0f;
	grassBlockTexCoords[27] = -1.0f;
	grassBlockTexCoords[28] = grassBlockTexCoords[16];
	grassBlockTexCoords[29] = grassBlockTexCoords[9];
	grassBlockTexCoords[30] = -1.0f;
	grassBlockTexCoords[31] = -1.0f;
	// BOTTOM
	grassBlockTexCoords[32] = mainAltas->getCoordX(8) + mainAltas->textureOffset;
	grassBlockTexCoords[33] = mainAltas->getCoordY(6) - mainAltas->textureOffset;
	grassBlockTexCoords[34] = -1.0f;
	grassBlockTexCoords[35] = -1.0f;
	grassBlockTexCoords[36] = mainAltas->getCoordX(9) - mainAltas->textureOffset;
	grassBlockTexCoords[37] = grassBlockTexCoords[33];
	grassBlockTexCoords[38] = -1.0f;
	grassBlockTexCoords[39] = -1.0f;
	grassBlockTexCoords[40] = grassBlockTexCoords[36];
	grassBlockTexCoords[41] = mainAltas->getCoordY(7) + mainAltas->textureOffset;
	grassBlockTexCoords[42] = -1.0f;
	grassBlockTexCoords[43] = -1.0f;
	grassBlockTexCoords[44] = grassBlockTexCoords[32];
	grassBlockTexCoords[45] = grassBlockTexCoords[41];
	grassBlockTexCoords[46] = -1.0f;
	grassBlockTexCoords[47] = -1.0f;

	grassBlockTexColors = new float[27];
	glm::vec3 grassColor = glm::pow(glm::vec3(0.474f, 0.752f, 0.352f), glm::vec3(2.2));

	grassBlockTexColors[0] = 1.0f;
	grassBlockTexColors[1] = 1.0f;
	grassBlockTexColors[2] = 1.0f;
	grassBlockTexColors[3] = grassColor.r;
	grassBlockTexColors[4] = grassColor.g;
	grassBlockTexColors[5] = grassColor.b;
	grassBlockTexColors[6] = grassColor.r;
	grassBlockTexColors[7] = grassColor.g;
	grassBlockTexColors[8] = grassColor.b;
	grassBlockTexColors[9] = 1.0f;
	grassBlockTexColors[10] = 1.0f;
	grassBlockTexColors[11] = 1.0f;
	grassBlockTexColors[12] = 1.0f;
	grassBlockTexColors[13] = 1.0f;
	grassBlockTexColors[14] = 1.0f;
	grassBlockTexColors[15] = 1.0f;
	grassBlockTexColors[16] = 1.0f;
	grassBlockTexColors[17] = 1.0f;
}