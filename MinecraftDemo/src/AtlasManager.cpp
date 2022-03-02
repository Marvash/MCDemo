#include "AtlasManager.h"

AtlasManager* AtlasManager::singleton;

AtlasManager::AtlasManager() : atlasWidth(0), atlasHeight(0), textureOffset(0.0f) {
	glGenTextures(1, &atlas);
}

void AtlasManager::loadAtlas(std::string& atlasBasePath, std::vector<std::string>& mipMapFilenames) {

	int width, height, nrChannels;
	std::stringstream completePath;
	int numMipMaps = mipMapFilenames.size();
	unsigned char* data;

	glBindTexture(GL_TEXTURE_2D, atlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, numMipMaps-1);

	stbi_set_flip_vertically_on_load(true);

	for (int i = 0; i < numMipMaps; i++) {
		completePath.str("");
		completePath << atlasBasePath << mipMapFilenames[i];
		data = stbi_load(completePath.str().c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum formatIn = GL_RGB;
			GLenum formatOut = GL_SRGB;
			if (nrChannels == 1) {
				formatIn = GL_RED;
				formatOut = GL_SRGB;
			}
			else if (nrChannels == 4) {
				formatIn = GL_RGBA;
				formatOut = GL_SRGB_ALPHA;
			}
			glTexImage2D(GL_TEXTURE_2D, i, formatOut, width, height, 0, formatIn, GL_UNSIGNED_BYTE, data);
			if (i == 0) {
				atlasWidth = width;
				atlasHeight = height;
			}
		}
		else
		{
			std::cout << "Failed to load texture " << completePath.str() << std::endl;
		}
		stbi_image_free(data);
	}
}

//Gets sprite texCoords starting from left
float AtlasManager::getCoordX(int spriteNum) {
	float spriteWidth = atlasWidth / numSpritesX;
	return (spriteWidth * spriteNum) / atlasWidth;
}

//Gets sprite texCoords starting from top
float AtlasManager::getCoordY(int spriteNum) {
	float spriteHeight = (atlasHeight / numSpritesY);
	return 1.0f - ((spriteHeight * spriteNum) / atlasHeight);
}

int AtlasManager::getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	switch (cubeId) {
	case Cube::CubeId::GRASS_BLOCK:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 0;
		case Cube::FaceSide::TOP:
			return 24;
		case Cube::FaceSide::BOTTOM:
			return 48;
		}
		break;
	case Cube::CubeId::DIRT_BLOCK:
		return 72;
	case Cube::CubeId::STONE_BLOCK:
		return 96;
	case Cube::CubeId::SAND_BLOCK:
		return 120;
	case Cube::CubeId::SNOWY_GRASS_BLOCK:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 144;
		case Cube::FaceSide::TOP:
			return 168;
		case Cube::FaceSide::BOTTOM:
			return 192;
		}
		break;
	case Cube::CubeId::OAK_LOG:
		switch (faceSide) {
		case Cube::FaceSide::RIGHT:
		case Cube::FaceSide::LEFT:
		case Cube::FaceSide::FRONT:
		case Cube::FaceSide::BACK:
			return 216;
		case Cube::FaceSide::TOP:
		case Cube::FaceSide::BOTTOM:
			return 240;
		}
		break;
	case Cube::CubeId::LEAVES:
		return 264;
		break;
	}
	return -1;
}

int AtlasManager::getBiomeCubeColors(Biome::BiomeId biomeId, Cube::CubeId cubeId, Cube::FaceSide faceSide) {
	switch (biomeId) {
	case Biome::BiomeId::TUNDRA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 198;
			case Cube::FaceSide::TOP:
				return 207;
			case Cube::FaceSide::BOTTOM:
				return 216;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::TAIGA:
		switch (cubeId) {
		case Cube::CubeId::SNOWY_GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 225;
			case Cube::FaceSide::TOP:
				return 234;
			case Cube::FaceSide::BOTTOM:
				return 243;
			}
			break;
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 36;
			case Cube::FaceSide::TOP:
				return 45;
			case Cube::FaceSide::BOTTOM:
				return 54;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::SAVANA:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 90;
			case Cube::FaceSide::TOP:
				return 99;
			case Cube::FaceSide::BOTTOM:
				return 108;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::DESERT:
		break;
	case Biome::BiomeId::MOUNTAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 117;
			case Cube::FaceSide::TOP:
				return 126;
			case Cube::FaceSide::BOTTOM:
				return 135;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::HILLS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 144;
			case Cube::FaceSide::TOP:
				return 153;
			case Cube::FaceSide::BOTTOM:
				return 162;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::PLAINS:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 9;
			case Cube::FaceSide::TOP:
				return 18;
			case Cube::FaceSide::BOTTOM:
				return 27;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::FOREST:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 63;
			case Cube::FaceSide::TOP:
				return 72;
			case Cube::FaceSide::BOTTOM:
				return 81;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	case Biome::BiomeId::JUNGLE:
		switch (cubeId) {
		case Cube::CubeId::GRASS_BLOCK:
			switch (faceSide) {
			case Cube::FaceSide::RIGHT:
			case Cube::FaceSide::LEFT:
			case Cube::FaceSide::FRONT:
			case Cube::FaceSide::BACK:
				return 171;
			case Cube::FaceSide::TOP:
				return 180;
			case Cube::FaceSide::BOTTOM:
				return 189;
			}
			break;
		case Cube::CubeId::LEAVES:
			return 252;
		}
		break;
	}
	return 0;
}

void AtlasManager::loadTextureBuffer() {
	glGenBuffers(1, &texDataBuffer);
	glBindBuffer(GL_TEXTURE_BUFFER, texDataBuffer);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * texDataSize, texData, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
	glGenTextures(1, &texDataImage);
	glBindTexture(GL_TEXTURE_BUFFER, texDataImage);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, texDataBuffer);
	glBindTexture(GL_TEXTURE_BUFFER, 0);
}

void AtlasManager::loadColorBuffer() {
	glGenBuffers(1, &colorDataBuffer);
	glBindBuffer(GL_TEXTURE_BUFFER, colorDataBuffer);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * colorDataSize, colorData, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
	glGenTextures(1, &colorDataImage);
	glBindTexture(GL_TEXTURE_BUFFER, colorDataImage);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, colorDataBuffer);
	glBindTexture(GL_TEXTURE_BUFFER, 0);
}

void AtlasManager::setTextureShaderUniforms(Shader& shader) {
	shader.setInt("texAtlas", 0);
	shader.setInt("vertexesTexData", 1);
	shader.setInt("vertexesColorData", 2);
}

void AtlasManager::bindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, texDataImage);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_BUFFER, colorDataImage);
}

void AtlasManager::init() {
	std::cout << "Loading atlas... " << std::endl;
	std::string atlasBasePath("assets/");
	std::vector<std::string> atlasFilenames;
	atlasFilenames.push_back(std::string("atlas0.png"));
	atlasFilenames.push_back(std::string("atlas1.png"));
	atlasFilenames.push_back(std::string("atlas2.png"));
	atlasFilenames.push_back(std::string("atlas3.png"));
	atlasFilenames.push_back(std::string("atlas4.png"));
	loadAtlas(atlasBasePath, atlasFilenames);
	std::cout << "Atlas loaded" << std::endl;

	texData = new GLfloat[texDataSize];

	// GRASS

	// SIDE
	// Top left
	texData[0] = getCoordX(12) + textureOffset;
	texData[1] = getCoordX(13) + textureOffset;
	texData[2] = -1.0f;
	texData[3] = getCoordY(10) - textureOffset;
	texData[4] = getCoordY(10) - textureOffset;
	texData[5] = -1.0f;
	// Top right
	texData[6] = getCoordX(13) - textureOffset;
	texData[7] = getCoordX(14) - textureOffset;
	texData[8] = -1.0f;
	texData[9] = getCoordY(10) - textureOffset;
	texData[10] = getCoordY(10) - textureOffset;
	texData[11] = -1.0f;
	// Bottom right
	texData[12] = getCoordX(13) - textureOffset;
	texData[13] = getCoordX(14) - textureOffset;
	texData[14] = -1.0f;
	texData[15] = getCoordY(11) + textureOffset;
	texData[16] = getCoordY(11) + textureOffset;
	texData[17] = -1.0f;
	// Bottom left
	texData[18] = getCoordX(12) + textureOffset;
	texData[19] = getCoordX(13) + textureOffset;
	texData[20] = -1.0f;
	texData[21] = getCoordY(11) + textureOffset;
	texData[22] = getCoordY(11) + textureOffset;
	texData[23] = -1.0f;

	// TOP
	// Top left
	texData[24] = getCoordX(15) + textureOffset;
	texData[25] = -1.0f;
	texData[26] = -1.0f;
	texData[27] = getCoordY(10) - textureOffset;
	texData[28] = -1.0f;
	texData[29] = -1.0f;
	// Top right
	texData[30] = getCoordX(16) - textureOffset;
	texData[31] = -1.0f;
	texData[32] = -1.0f;
	texData[33] = getCoordY(10) - textureOffset;
	texData[34] = -1.0f;
	texData[35] = -1.0f;
	// Bottom right
	texData[36] = getCoordX(16) - textureOffset;
	texData[37] = -1.0f;
	texData[38] = -1.0f;
	texData[39] = getCoordY(11) + textureOffset;
	texData[40] = -1.0f;
	texData[41] = -1.0f;
	// Bottom left
	texData[42] = getCoordX(15) + textureOffset;
	texData[43] = -1.0f;
	texData[44] = -1.0f;
	texData[45] = getCoordY(11) + textureOffset;
	texData[46] = -1.0f;
	texData[47] = -1.0f;

	// BOTTOM
	// Top left
	texData[48] = getCoordX(8) + textureOffset;
	texData[49] = -1.0f;
	texData[50] = -1.0f;
	texData[51] = getCoordY(6) - textureOffset;
	texData[52] = -1.0f;
	texData[53] = -1.0f;
	// Top right
	texData[54] = getCoordX(9) - textureOffset;
	texData[55] = -1.0f;
	texData[56] = -1.0f;
	texData[57] = getCoordY(6) - textureOffset;
	texData[58] = -1.0f;
	texData[59] = -1.0f;
	// Bottom right
	texData[60] = getCoordX(9) - textureOffset;
	texData[61] = -1.0f;
	texData[62] = -1.0f;
	texData[63] = getCoordY(7) + textureOffset;
	texData[64] = -1.0f;
	texData[65] = -1.0f;
	// Bottom left
	texData[66] = getCoordX(8) + textureOffset;
	texData[67] = -1.0f;
	texData[68] = -1.0f;
	texData[69] = getCoordY(7) + textureOffset;
	texData[70] = -1.0f;
	texData[71] = -1.0f;

	// DIRT

	// BOTTOM
	// Top left
	texData[72] = getCoordX(8) + textureOffset;
	texData[73] = -1.0f;
	texData[74] = -1.0f;
	texData[75] = getCoordY(6) - textureOffset;
	texData[76] = -1.0f;
	texData[77] = -1.0f;
	// Top right
	texData[78] = getCoordX(9) - textureOffset;
	texData[79] = -1.0f;
	texData[80] = -1.0f;
	texData[81] = getCoordY(6) - textureOffset;
	texData[82] = -1.0f;
	texData[83] = -1.0f;
	// Bottom right
	texData[84] = getCoordX(9) - textureOffset;
	texData[85] = -1.0f;
	texData[86] = -1.0f;
	texData[87] = getCoordY(7) + textureOffset;
	texData[88] = -1.0f;
	texData[89] = -1.0f;
	// Bottom left
	texData[90] = getCoordX(8) + textureOffset;
	texData[91] = -1.0f;
	texData[92] = -1.0f;
	texData[93] = getCoordY(7) + textureOffset;
	texData[94] = -1.0f;
	texData[95] = -1.0f;

	// STONE

	// BOTTOM
	// Top left
	texData[96] = getCoordX(20) + textureOffset;
	texData[97] = -1.0f;
	texData[98] = -1.0f;
	texData[99] = getCoordY(9) - textureOffset;
	texData[100] = -1.0f;
	texData[101] = -1.0f;
	// Top right
	texData[102] = getCoordX(21) - textureOffset;
	texData[103] = -1.0f;
	texData[104] = -1.0f;
	texData[105] = getCoordY(9) - textureOffset;
	texData[106] = -1.0f;
	texData[107] = -1.0f;
	// Bottom right
	texData[108] = getCoordX(21) - textureOffset;
	texData[109] = -1.0f;
	texData[110] = -1.0f;
	texData[111] = getCoordY(10) + textureOffset;
	texData[112] = -1.0f;
	texData[113] = -1.0f;
	// Bottom left
	texData[114] = getCoordX(20) + textureOffset;
	texData[115] = -1.0f;
	texData[116] = -1.0f;
	texData[117] = getCoordY(10) + textureOffset;
	texData[118] = -1.0f;
	texData[119] = -1.0f;

	// SAND

	// BOTTOM
	// Top left
	texData[120] = getCoordX(19) + textureOffset;
	texData[121] = -1.0f;
	texData[122] = -1.0f;
	texData[123] = getCoordY(7) - textureOffset;
	texData[124] = -1.0f;
	texData[125] = -1.0f;
	// Top right
	texData[126] = getCoordX(20) - textureOffset;
	texData[127] = -1.0f;
	texData[128] = -1.0f;
	texData[129] = getCoordY(7) - textureOffset;
	texData[130] = -1.0f;
	texData[131] = -1.0f;
	// Bottom right
	texData[132] = getCoordX(20) - textureOffset;
	texData[133] = -1.0f;
	texData[134] = -1.0f;
	texData[135] = getCoordY(8) + textureOffset;
	texData[136] = -1.0f;
	texData[137] = -1.0f;
	// Bottom left
	texData[138] = getCoordX(19) + textureOffset;
	texData[139] = -1.0f;
	texData[140] = -1.0f;
	texData[141] = getCoordY(8) + textureOffset;
	texData[142] = -1.0f;
	texData[143] = -1.0f;

	// SNOWY GRASS

	// SIDE
	// Top left
	texData[144] = getCoordX(14) + textureOffset;
	texData[145] = -1.0f;
	texData[146] = -1.0f;
	texData[147] = getCoordY(10) - textureOffset;
	texData[148] = -1.0f;
	texData[149] = -1.0f;
	// Top right
	texData[150] = getCoordX(15) - textureOffset;
	texData[151] = -1.0f;
	texData[152] = -1.0f;
	texData[153] = getCoordY(10) - textureOffset;
	texData[154] = -1.0f;
	texData[155] = -1.0f;
	// Bottom right
	texData[156] = getCoordX(15) - textureOffset;
	texData[157] = -1.0f;
	texData[158] = -1.0f;
	texData[159] = getCoordY(11) + textureOffset;
	texData[160] = -1.0f;
	texData[161] = -1.0f;
	// Bottom left
	texData[162] = getCoordX(14) + textureOffset;
	texData[163] = -1.0f;
	texData[164] = -1.0f;
	texData[165] = getCoordY(11) + textureOffset;
	texData[166] = -1.0f;
	texData[167] = -1.0f;

	// TOP
	// Top left
	texData[168] = getCoordX(15) + textureOffset;
	texData[169] = -1.0f;
	texData[170] = -1.0f;
	texData[171] = getCoordY(10) - textureOffset;
	texData[172] = -1.0f;
	texData[173] = -1.0f;
	// Top right
	texData[174] = getCoordX(16) - textureOffset;
	texData[175] = -1.0f;
	texData[176] = -1.0f;
	texData[177] = getCoordY(10) - textureOffset;
	texData[178] = -1.0f;
	texData[179] = -1.0f;
	// Bottom right
	texData[180] = getCoordX(16) - textureOffset;
	texData[181] = -1.0f;
	texData[182] = -1.0f;
	texData[183] = getCoordY(11) + textureOffset;
	texData[184] = -1.0f;
	texData[185] = -1.0f;
	// Bottom left
	texData[186] = getCoordX(15) + textureOffset;
	texData[187] = -1.0f;
	texData[188] = -1.0f;
	texData[189] = getCoordY(11) + textureOffset;
	texData[190] = -1.0f;
	texData[191] = -1.0f;

	// BOTTOM
	// Top left
	texData[192] = getCoordX(8) + textureOffset;
	texData[193] = -1.0f;
	texData[194] = -1.0f;
	texData[195] = getCoordY(6) - textureOffset;
	texData[196] = -1.0f;
	texData[197] = -1.0f;
	// Top right
	texData[198] = getCoordX(9) - textureOffset;
	texData[199] = -1.0f;
	texData[200] = -1.0f;
	texData[201] = getCoordY(6) - textureOffset;
	texData[202] = -1.0f;
	texData[203] = -1.0f;
	// Bottom right
	texData[204] = getCoordX(9) - textureOffset;
	texData[205] = -1.0f;
	texData[206] = -1.0f;
	texData[207] = getCoordY(7) + textureOffset;
	texData[208] = -1.0f;
	texData[209] = -1.0f;
	// Bottom left
	texData[210] = getCoordX(8) + textureOffset;
	texData[211] = -1.0f;
	texData[212] = -1.0f;
	texData[213] = getCoordY(7) + textureOffset;
	texData[214] = -1.0f;
	texData[215] = -1.0f;

	// OAK LOG

	// SIDE
	// Top left
	texData[216] = getCoordX(3) + textureOffset;
	texData[217] = -1.0f;
	texData[218] = -1.0f;
	texData[219] = getCoordY(14) - textureOffset;
	texData[220] = -1.0f;
	texData[221] = -1.0f;
	// Top right
	texData[222] = getCoordX(4) - textureOffset;
	texData[223] = -1.0f;
	texData[224] = -1.0f;
	texData[225] = getCoordY(14) - textureOffset;
	texData[226] = -1.0f;
	texData[227] = -1.0f;
	// Bottom right
	texData[228] = getCoordX(4) - textureOffset;
	texData[229] = -1.0f;
	texData[230] = -1.0f;
	texData[231] = getCoordY(15) + textureOffset;
	texData[232] = -1.0f;
	texData[233] = -1.0f;
	// Bottom left
	texData[234] = getCoordX(3) + textureOffset;
	texData[235] = -1.0f;
	texData[236] = -1.0f;
	texData[237] = getCoordY(15) + textureOffset;
	texData[238] = -1.0f;
	texData[239] = -1.0f;

	// BOTTOM
	// Top left
	texData[240] = getCoordX(4) + textureOffset;
	texData[241] = -1.0f;
	texData[242] = -1.0f;
	texData[243] = getCoordY(14) - textureOffset;
	texData[244] = -1.0f;
	texData[245] = -1.0f;
	// Top right
	texData[246] = getCoordX(5) - textureOffset;
	texData[247] = -1.0f;
	texData[248] = -1.0f;
	texData[249] = getCoordY(14) - textureOffset;
	texData[250] = -1.0f;
	texData[251] = -1.0f;
	// Bottom right
	texData[252] = getCoordX(5) - textureOffset;
	texData[253] = -1.0f;
	texData[254] = -1.0f;
	texData[255] = getCoordY(15) + textureOffset;
	texData[256] = -1.0f;
	texData[257] = -1.0f;
	// Bottom left
	texData[258] = getCoordX(4) + textureOffset;
	texData[259] = -1.0f;
	texData[260] = -1.0f;
	texData[261] = getCoordY(15) + textureOffset;
	texData[262] = -1.0f;
	texData[263] = -1.0f;

	// LEAVES

	// BOTTOM
	// Top left
	texData[264] = getCoordX(4) + textureOffset;
	texData[265] = -1.0f;
	texData[266] = -1.0f;
	texData[267] = getCoordY(13) - textureOffset;
	texData[268] = -1.0f;
	texData[269] = -1.0f;
	// Top right
	texData[270] = getCoordX(5) - textureOffset;
	texData[271] = -1.0f;
	texData[272] = -1.0f;
	texData[273] = getCoordY(13) - textureOffset;
	texData[274] = -1.0f;
	texData[275] = -1.0f;
	// Bottom right
	texData[276] = getCoordX(5) - textureOffset;
	texData[277] = -1.0f;
	texData[278] = -1.0f;
	texData[279] = getCoordY(14) + textureOffset;
	texData[280] = -1.0f;
	texData[281] = -1.0f;
	// Bottom left
	texData[282] = getCoordX(4) + textureOffset;
	texData[283] = -1.0f;
	texData[284] = -1.0f;
	texData[285] = getCoordY(14) + textureOffset;
	texData[286] = -1.0f;
	texData[287] = -1.0f;

	std::cout << "Loading texture buffer... " << std::endl;
	loadTextureBuffer();
	std::cout << "Texture buffer loaded" << std::endl;

	colorData = new GLfloat[colorDataSize];

	// DEFAULT

	colorData[0] = 1.0f;
	colorData[1] = 1.0f;
	colorData[2] = 1.0f;
	colorData[3] = 1.0f;
	colorData[4] = 1.0f;
	colorData[5] = 1.0f;
	colorData[6] = 1.0f;
	colorData[7] = 1.0f;
	colorData[8] = 1.0f;

	// GRASS CUBE

	glm::vec3 plainsGrassColor = glm::pow(glm::vec3(0.568f, 0.741f, 0.349f), glm::vec3(2.2));
	glm::vec3 taigaGrassColor = glm::pow(glm::vec3(0.525f, 0.717f, 0.513f), glm::vec3(2.2));
	glm::vec3 forestGrassColor = glm::pow(glm::vec3(0.474f, 0.752f, 0.352f), glm::vec3(2.2));
	glm::vec3 savanaGrassColor = glm::pow(glm::vec3(0.749f, 0.717f, 0.333f), glm::vec3(2.2));
	glm::vec3 mountainsGrassColor = glm::pow(glm::vec3(0.603f, 0.745f, 0.294f), glm::vec3(2.2));
	glm::vec3 hillsGrassColor = glm::pow(glm::vec3(0.541f, 0.713f, 0.537f), glm::vec3(2.2));
	glm::vec3 jungleGrassColor = glm::pow(glm::vec3(0.349f, 0.788f, 0.235f), glm::vec3(2.2));

	//---
	colorData[9] = 1.0f;
	colorData[10] = 1.0f;
	colorData[11] = 1.0f;
	colorData[12] = plainsGrassColor.r;
	colorData[13] = plainsGrassColor.g;
	colorData[14] = plainsGrassColor.b;
	colorData[15] = 1.0f;
	colorData[16] = 1.0f;
	colorData[17] = 1.0f;

	colorData[18] = plainsGrassColor.r;
	colorData[19] = plainsGrassColor.g;
	colorData[20] = plainsGrassColor.b;
	colorData[21] = 1.0f;
	colorData[22] = 1.0f;
	colorData[23] = 1.0f;
	colorData[24] = 1.0f;
	colorData[25] = 1.0f;
	colorData[26] = 1.0f;

	colorData[27] = 1.0f;
	colorData[28] = 1.0f;
	colorData[29] = 1.0f;
	colorData[30] = 1.0f;
	colorData[31] = 1.0f;
	colorData[32] = 1.0f;
	colorData[33] = 1.0f;
	colorData[34] = 1.0f;
	colorData[35] = 1.0f;
	//---
	colorData[36] = 1.0f;
	colorData[37] = 1.0f;
	colorData[38] = 1.0f;
	colorData[39] = taigaGrassColor.r;
	colorData[40] = taigaGrassColor.g;
	colorData[41] = taigaGrassColor.b;
	colorData[42] = 1.0f;
	colorData[43] = 1.0f;
	colorData[44] = 1.0f;

	colorData[45] = taigaGrassColor.r;
	colorData[46] = taigaGrassColor.g;
	colorData[47] = taigaGrassColor.b;
	colorData[48] = 1.0f;
	colorData[49] = 1.0f;
	colorData[50] = 1.0f;
	colorData[51] = 1.0f;
	colorData[52] = 1.0f;
	colorData[53] = 1.0f;

	colorData[54] = 1.0f;
	colorData[55] = 1.0f;
	colorData[56] = 1.0f;
	colorData[57] = 1.0f;
	colorData[58] = 1.0f;
	colorData[59] = 1.0f;
	colorData[60] = 1.0f;
	colorData[61] = 1.0f;
	colorData[62] = 1.0f;
	//---
	colorData[63] = 1.0f;
	colorData[64] = 1.0f;
	colorData[65] = 1.0f;
	colorData[66] = forestGrassColor.r;
	colorData[67] = forestGrassColor.g;
	colorData[68] = forestGrassColor.b;
	colorData[69] = 1.0f;
	colorData[70] = 1.0f;
	colorData[71] = 1.0f;

	colorData[72] = forestGrassColor.r;
	colorData[73] = forestGrassColor.g;
	colorData[74] = forestGrassColor.b;
	colorData[75] = 1.0f;
	colorData[76] = 1.0f;
	colorData[77] = 1.0f;
	colorData[78] = 1.0f;
	colorData[79] = 1.0f;
	colorData[80] = 1.0f;

	colorData[81] = 1.0f;
	colorData[82] = 1.0f;
	colorData[83] = 1.0f;
	colorData[84] = 1.0f;
	colorData[85] = 1.0f;
	colorData[86] = 1.0f;
	colorData[87] = 1.0f;
	colorData[88] = 1.0f;
	colorData[89] = 1.0f;
	//---
	colorData[90] = 1.0f;
	colorData[91] = 1.0f;
	colorData[92] = 1.0f;
	colorData[93] = savanaGrassColor.r;
	colorData[94] = savanaGrassColor.g;
	colorData[95] = savanaGrassColor.b;
	colorData[96] = 1.0f;
	colorData[97] = 1.0f;
	colorData[98] = 1.0f;

	colorData[99] = savanaGrassColor.r;
	colorData[100] = savanaGrassColor.g;
	colorData[101] = savanaGrassColor.b;
	colorData[102] = 1.0f;
	colorData[103] = 1.0f;
	colorData[104] = 1.0f;
	colorData[105] = 1.0f;
	colorData[106] = 1.0f;
	colorData[107] = 1.0f;

	colorData[108] = 1.0f;
	colorData[109] = 1.0f;
	colorData[110] = 1.0f;
	colorData[111] = 1.0f;
	colorData[112] = 1.0f;
	colorData[113] = 1.0f;
	colorData[114] = 1.0f;
	colorData[115] = 1.0f;
	colorData[116] = 1.0f;
	//---
	colorData[117] = 1.0f;
	colorData[118] = 1.0f;
	colorData[119] = 1.0f;
	colorData[120] = mountainsGrassColor.r;
	colorData[121] = mountainsGrassColor.g;
	colorData[122] = mountainsGrassColor.b;
	colorData[123] = 1.0f;
	colorData[124] = 1.0f;
	colorData[125] = 1.0f;

	colorData[126] = mountainsGrassColor.r;
	colorData[127] = mountainsGrassColor.g;
	colorData[128] = mountainsGrassColor.b;
	colorData[129] = 1.0f;
	colorData[130] = 1.0f;
	colorData[131] = 1.0f;
	colorData[132] = 1.0f;
	colorData[133] = 1.0f;
	colorData[134] = 1.0f;

	colorData[135] = 1.0f;
	colorData[136] = 1.0f;
	colorData[137] = 1.0f;
	colorData[138] = 1.0f;
	colorData[139] = 1.0f;
	colorData[140] = 1.0f;
	colorData[141] = 1.0f;
	colorData[142] = 1.0f;
	colorData[143] = 1.0f;
	//---
	colorData[144] = 1.0f;
	colorData[145] = 1.0f;
	colorData[146] = 1.0f;
	colorData[147] = hillsGrassColor.r;
	colorData[148] = hillsGrassColor.g;
	colorData[149] = hillsGrassColor.b;
	colorData[150] = 1.0f;
	colorData[151] = 1.0f;
	colorData[152] = 1.0f;

	colorData[153] = hillsGrassColor.r;
	colorData[154] = hillsGrassColor.g;
	colorData[155] = hillsGrassColor.b;
	colorData[156] = 1.0f;
	colorData[157] = 1.0f;
	colorData[158] = 1.0f;
	colorData[159] = 1.0f;
	colorData[160] = 1.0f;
	colorData[161] = 1.0f;

	colorData[162] = 1.0f;
	colorData[163] = 1.0f;
	colorData[164] = 1.0f;
	colorData[165] = 1.0f;
	colorData[166] = 1.0f;
	colorData[167] = 1.0f;
	colorData[168] = 1.0f;
	colorData[169] = 1.0f;
	colorData[170] = 1.0f;
	//---
	colorData[171] = 1.0f;
	colorData[172] = 1.0f;
	colorData[173] = 1.0f;
	colorData[174] = jungleGrassColor.r;
	colorData[175] = jungleGrassColor.g;
	colorData[176] = jungleGrassColor.b;
	colorData[177] = 1.0f;
	colorData[178] = 1.0f;
	colorData[179] = 1.0f;

	colorData[180] = jungleGrassColor.r;
	colorData[181] = jungleGrassColor.g;
	colorData[182] = jungleGrassColor.b;
	colorData[183] = 1.0f;
	colorData[184] = 1.0f;
	colorData[185] = 1.0f;
	colorData[186] = 1.0f;
	colorData[187] = 1.0f;
	colorData[188] = 1.0f;

	colorData[189] = 1.0f;
	colorData[190] = 1.0f;
	colorData[191] = 1.0f;
	colorData[192] = 1.0f;
	colorData[193] = 1.0f;
	colorData[194] = 1.0f;
	colorData[195] = 1.0f;
	colorData[196] = 1.0f;
	colorData[197] = 1.0f;

	// SNOWY GRASS CUBE

	glm::vec3 taigaSnowyGrassColor = glm::pow(glm::vec3(0.525f, 0.717f, 0.513f), glm::vec3(2.2));
	glm::vec3 tundraSnowyGrassColor = glm::pow(glm::vec3(0.501f, 0.705f, 0.592f), glm::vec3(2.2));
	//--- TUNDRA
	colorData[198] = 1.0f;
	colorData[199] = 1.0f;
	colorData[200] = 1.0f;
	colorData[201] = 1.0f;
	colorData[202] = 1.0f;
	colorData[203] = 1.0f;
	colorData[204] = 1.0f;
	colorData[205] = 1.0f;
	colorData[206] = 1.0f;

	colorData[207] = tundraSnowyGrassColor.r;
	colorData[208] = tundraSnowyGrassColor.g;
	colorData[209] = tundraSnowyGrassColor.b;
	colorData[210] = 1.0f;
	colorData[211] = 1.0f;
	colorData[212] = 1.0f;
	colorData[213] = 1.0f;
	colorData[214] = 1.0f;
	colorData[215] = 1.0f;

	colorData[216] = 1.0f;
	colorData[217] = 1.0f;
	colorData[218] = 1.0f;
	colorData[219] = 1.0f;
	colorData[220] = 1.0f;
	colorData[221] = 1.0f;
	colorData[222] = 1.0f;
	colorData[223] = 1.0f;
	colorData[224] = 1.0f;
	//--- TAIGA
	colorData[225] = 1.0f;
	colorData[226] = 1.0f;
	colorData[227] = 1.0f;
	colorData[228] = 1.0f;
	colorData[229] = 1.0f;
	colorData[230] = 1.0f;
	colorData[231] = 1.0f;
	colorData[232] = 1.0f;
	colorData[233] = 1.0f;

	colorData[234] = taigaSnowyGrassColor.r;
	colorData[235] = taigaSnowyGrassColor.g;
	colorData[236] = taigaSnowyGrassColor.b;
	colorData[237] = 1.0f;
	colorData[238] = 1.0f;
	colorData[239] = 1.0f;
	colorData[240] = 1.0f;
	colorData[241] = 1.0f;
	colorData[242] = 1.0f;

	colorData[243] = 1.0f;
	colorData[244] = 1.0f;
	colorData[245] = 1.0f;
	colorData[246] = 1.0f;
	colorData[247] = 1.0f;
	colorData[248] = 1.0f;
	colorData[249] = 1.0f;
	colorData[250] = 1.0f;
	colorData[251] = 1.0f;
	//---

	// LEAVES

	glm::vec3 forestLeavesColor = glm::pow(glm::vec3(0.349f, 0.682f, 0.188f), glm::vec3(2.2));

	//--- FOREST
	colorData[252] = forestLeavesColor.r;
	colorData[253] = forestLeavesColor.g;
	colorData[254] = forestLeavesColor.b;
	colorData[255] = 1.0f;
	colorData[256] = 1.0f;
	colorData[257] = 1.0f;
	colorData[258] = 1.0f;
	colorData[259] = 1.0f;
	colorData[260] = 1.0f;
	//---

	std::cout << "Loading color buffer... " << std::endl;
	loadColorBuffer();
	std::cout << "Color buffer loaded" << std::endl;
}

AtlasManager* AtlasManager::instance() {
	if (singleton == nullptr) {
		singleton = new AtlasManager();
	}
	return singleton;
}