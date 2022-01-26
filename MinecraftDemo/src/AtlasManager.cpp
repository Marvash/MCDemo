#include "AtlasManager.h"

AtlasManager* AtlasManager::singleton;

AtlasManager::AtlasManager() : atlasWidth(0), atlasHeight(0), textureOffset(0.0001f) {
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

void AtlasManager::loadTextureBuffer() {
	glGenBuffers(1, &texDataBuffer);
	glBindBuffer(GL_TEXTURE_BUFFER, texDataBuffer);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * texDataSize, texData, GL_STATIC_DRAW);
	glGenTextures(1, &texDataImage);
	glBindTexture(GL_TEXTURE_BUFFER, texDataImage);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, texDataBuffer);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

void AtlasManager::setTextureShaderUniforms(Shader& shader) {
	shader.setInt("texAtlas", 0);
	shader.setInt("vertexesTexData", 1);
}

void AtlasManager::bindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, texDataImage);
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

	// SIDE 0 23
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

	// TOP 24 47
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

	// BOTTOM 48 71
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

	glm::vec3 grassColor = glm::pow(glm::vec3(0.474f, 0.752f, 0.352f), glm::vec3(2.2));

	// 72 80
	texData[72] = 1.0f;
	texData[73] = 1.0f;
	texData[74] = 1.0f;
	texData[75] = grassColor.r;
	texData[76] = grassColor.g;
	texData[77] = grassColor.b;
	texData[78] = 1.0f;
	texData[79] = 1.0f;
	texData[80] = 1.0f;
	// 81 89
	texData[81] = grassColor.r;
	texData[82] = grassColor.g;
	texData[83] = grassColor.b;
	texData[84] = 1.0f;
	texData[85] = 1.0f;
	texData[86] = 1.0f;
	texData[87] = 1.0f;
	texData[88] = 1.0f;
	texData[89] = 1.0f;
	// 90 98 
	texData[90] = 1.0f;
	texData[91] = 1.0f;
	texData[92] = 1.0f;
	texData[93] = 1.0f;
	texData[94] = 1.0f;
	texData[95] = 1.0f;
	texData[96] = 1.0f;
	texData[97] = 1.0f;
	texData[98] = 1.0f;

	// DIRT

	// BOTTOM 99 122
	texData[99] = getCoordX(8) + textureOffset;
	texData[100] = -1.0f;
	texData[101] = -1.0f;
	texData[102] = getCoordY(6) - textureOffset;
	texData[103] = -1.0f;
	texData[104] = -1.0f;
	// Top right
	texData[105] = getCoordX(9) - textureOffset;
	texData[106] = -1.0f;
	texData[107] = -1.0f;
	texData[108] = getCoordY(6) - textureOffset;
	texData[109] = -1.0f;
	texData[110] = -1.0f;
	// Bottom right
	texData[111] = getCoordX(9) - textureOffset;
	texData[112] = -1.0f;
	texData[113] = -1.0f;
	texData[114] = getCoordY(7) + textureOffset;
	texData[115] = -1.0f;
	texData[116] = -1.0f;
	// Bottom left
	texData[117] = getCoordX(8) + textureOffset;
	texData[118] = -1.0f;
	texData[119] = -1.0f;
	texData[120] = getCoordY(7) + textureOffset;
	texData[121] = -1.0f;
	texData[122] = -1.0f;

	// 123 131
	texData[123] = 1.0f;
	texData[124] = 1.0f;
	texData[125] = 1.0f;
	texData[126] = 1.0f;
	texData[127] = 1.0f;
	texData[128] = 1.0f;
	texData[129] = 1.0f;
	texData[130] = 1.0f;
	texData[131] = 1.0f;

	// STONE

	// BOTTOM 132 155
	// Top left
	texData[132] = getCoordX(20) + textureOffset;
	texData[133] = -1.0f;
	texData[134] = -1.0f;
	texData[135] = getCoordY(9) - textureOffset;
	texData[136] = -1.0f;
	texData[137] = -1.0f;
	// Top right
	texData[138] = getCoordX(21) - textureOffset;
	texData[139] = -1.0f;
	texData[140] = -1.0f;
	texData[141] = getCoordY(9) - textureOffset;
	texData[142] = -1.0f;
	texData[143] = -1.0f;
	// Bottom right
	texData[144] = getCoordX(21) - textureOffset;
	texData[145] = -1.0f;
	texData[146] = -1.0f;
	texData[147] = getCoordY(10) + textureOffset;
	texData[148] = -1.0f;
	texData[149] = -1.0f;
	// Bottom left
	texData[150] = getCoordX(20) + textureOffset;
	texData[151] = -1.0f;
	texData[152] = -1.0f;
	texData[153] = getCoordY(10) + textureOffset;
	texData[154] = -1.0f;
	texData[155] = -1.0f;

	// BOTTOM 156 164
	texData[156] = 1.0f;
	texData[157] = 1.0f;
	texData[158] = 1.0f;
	texData[159] = 1.0f;
	texData[160] = 1.0f;
	texData[161] = 1.0f;
	texData[162] = 1.0f;
	texData[163] = 1.0f;
	texData[164] = 1.0f;

	std::cout << "Loading texture buffer... " << std::endl;
	loadTextureBuffer();
	std::cout << "Texture buffer loaded" << std::endl;
}

AtlasManager* AtlasManager::instance() {
	if (singleton == nullptr) {
		singleton = new AtlasManager();
	}
	return singleton;
}