#include "BiomeColors.h"

BiomeColors::BiomeColors() {
	m_biomeColorsArray = new GLfloat[TEX_COLORS_SIZE];

	// DEFAULT (no color)

	m_biomeColorsArray[0] = 1.0f;
	m_biomeColorsArray[1] = 1.0f;
	m_biomeColorsArray[2] = 1.0f;
	m_biomeColorsArray[3] = 1.0f;
	m_biomeColorsArray[4] = 1.0f;
	m_biomeColorsArray[5] = 1.0f;
	m_biomeColorsArray[6] = 1.0f;
	m_biomeColorsArray[7] = 1.0f;
	m_biomeColorsArray[8] = 1.0f;

	// GRASS CUBE

	glm::vec3 plainsGrassColor = glm::pow(glm::vec3(0.568f, 0.741f, 0.349f), glm::vec3(2.2));
	glm::vec3 taigaGrassColor = glm::pow(glm::vec3(0.525f, 0.717f, 0.513f), glm::vec3(2.2));
	glm::vec3 forestGrassColor = glm::pow(glm::vec3(0.474f, 0.752f, 0.352f), glm::vec3(2.2));
	glm::vec3 savanaGrassColor = glm::pow(glm::vec3(0.749f, 0.717f, 0.333f), glm::vec3(2.2));
	glm::vec3 mountainsGrassColor = glm::pow(glm::vec3(0.603f, 0.745f, 0.294f), glm::vec3(2.2));
	glm::vec3 hillsGrassColor = glm::pow(glm::vec3(0.541f, 0.713f, 0.537f), glm::vec3(2.2));
	glm::vec3 jungleGrassColor = glm::pow(glm::vec3(0.349f, 0.788f, 0.235f), glm::vec3(2.2));

	//---
	m_biomeColorsArray[9] = 1.0f;
	m_biomeColorsArray[10] = 1.0f;
	m_biomeColorsArray[11] = 1.0f;
	m_biomeColorsArray[12] = plainsGrassColor.r;
	m_biomeColorsArray[13] = plainsGrassColor.g;
	m_biomeColorsArray[14] = plainsGrassColor.b;
	m_biomeColorsArray[15] = 1.0f;
	m_biomeColorsArray[16] = 1.0f;
	m_biomeColorsArray[17] = 1.0f;

	m_biomeColorsArray[18] = plainsGrassColor.r;
	m_biomeColorsArray[19] = plainsGrassColor.g;
	m_biomeColorsArray[20] = plainsGrassColor.b;
	m_biomeColorsArray[21] = 1.0f;
	m_biomeColorsArray[22] = 1.0f;
	m_biomeColorsArray[23] = 1.0f;
	m_biomeColorsArray[24] = 1.0f;
	m_biomeColorsArray[25] = 1.0f;
	m_biomeColorsArray[26] = 1.0f;

	m_biomeColorsArray[27] = 1.0f;
	m_biomeColorsArray[28] = 1.0f;
	m_biomeColorsArray[29] = 1.0f;
	m_biomeColorsArray[30] = 1.0f;
	m_biomeColorsArray[31] = 1.0f;
	m_biomeColorsArray[32] = 1.0f;
	m_biomeColorsArray[33] = 1.0f;
	m_biomeColorsArray[34] = 1.0f;
	m_biomeColorsArray[35] = 1.0f;
	//---
	m_biomeColorsArray[36] = 1.0f;
	m_biomeColorsArray[37] = 1.0f;
	m_biomeColorsArray[38] = 1.0f;
	m_biomeColorsArray[39] = taigaGrassColor.r;
	m_biomeColorsArray[40] = taigaGrassColor.g;
	m_biomeColorsArray[41] = taigaGrassColor.b;
	m_biomeColorsArray[42] = 1.0f;
	m_biomeColorsArray[43] = 1.0f;
	m_biomeColorsArray[44] = 1.0f;

	m_biomeColorsArray[45] = taigaGrassColor.r;
	m_biomeColorsArray[46] = taigaGrassColor.g;
	m_biomeColorsArray[47] = taigaGrassColor.b;
	m_biomeColorsArray[48] = 1.0f;
	m_biomeColorsArray[49] = 1.0f;
	m_biomeColorsArray[50] = 1.0f;
	m_biomeColorsArray[51] = 1.0f;
	m_biomeColorsArray[52] = 1.0f;
	m_biomeColorsArray[53] = 1.0f;

	m_biomeColorsArray[54] = 1.0f;
	m_biomeColorsArray[55] = 1.0f;
	m_biomeColorsArray[56] = 1.0f;
	m_biomeColorsArray[57] = 1.0f;
	m_biomeColorsArray[58] = 1.0f;
	m_biomeColorsArray[59] = 1.0f;
	m_biomeColorsArray[60] = 1.0f;
	m_biomeColorsArray[61] = 1.0f;
	m_biomeColorsArray[62] = 1.0f;
	//---
	m_biomeColorsArray[63] = 1.0f;
	m_biomeColorsArray[64] = 1.0f;
	m_biomeColorsArray[65] = 1.0f;
	m_biomeColorsArray[66] = forestGrassColor.r;
	m_biomeColorsArray[67] = forestGrassColor.g;
	m_biomeColorsArray[68] = forestGrassColor.b;
	m_biomeColorsArray[69] = 1.0f;
	m_biomeColorsArray[70] = 1.0f;
	m_biomeColorsArray[71] = 1.0f;

	m_biomeColorsArray[72] = forestGrassColor.r;
	m_biomeColorsArray[73] = forestGrassColor.g;
	m_biomeColorsArray[74] = forestGrassColor.b;
	m_biomeColorsArray[75] = 1.0f;
	m_biomeColorsArray[76] = 1.0f;
	m_biomeColorsArray[77] = 1.0f;
	m_biomeColorsArray[78] = 1.0f;
	m_biomeColorsArray[79] = 1.0f;
	m_biomeColorsArray[80] = 1.0f;

	m_biomeColorsArray[81] = 1.0f;
	m_biomeColorsArray[82] = 1.0f;
	m_biomeColorsArray[83] = 1.0f;
	m_biomeColorsArray[84] = 1.0f;
	m_biomeColorsArray[85] = 1.0f;
	m_biomeColorsArray[86] = 1.0f;
	m_biomeColorsArray[87] = 1.0f;
	m_biomeColorsArray[88] = 1.0f;
	m_biomeColorsArray[89] = 1.0f;
	//---
	m_biomeColorsArray[90] = 1.0f;
	m_biomeColorsArray[91] = 1.0f;
	m_biomeColorsArray[92] = 1.0f;
	m_biomeColorsArray[93] = savanaGrassColor.r;
	m_biomeColorsArray[94] = savanaGrassColor.g;
	m_biomeColorsArray[95] = savanaGrassColor.b;
	m_biomeColorsArray[96] = 1.0f;
	m_biomeColorsArray[97] = 1.0f;
	m_biomeColorsArray[98] = 1.0f;

	m_biomeColorsArray[99] = savanaGrassColor.r;
	m_biomeColorsArray[100] = savanaGrassColor.g;
	m_biomeColorsArray[101] = savanaGrassColor.b;
	m_biomeColorsArray[102] = 1.0f;
	m_biomeColorsArray[103] = 1.0f;
	m_biomeColorsArray[104] = 1.0f;
	m_biomeColorsArray[105] = 1.0f;
	m_biomeColorsArray[106] = 1.0f;
	m_biomeColorsArray[107] = 1.0f;

	m_biomeColorsArray[108] = 1.0f;
	m_biomeColorsArray[109] = 1.0f;
	m_biomeColorsArray[110] = 1.0f;
	m_biomeColorsArray[111] = 1.0f;
	m_biomeColorsArray[112] = 1.0f;
	m_biomeColorsArray[113] = 1.0f;
	m_biomeColorsArray[114] = 1.0f;
	m_biomeColorsArray[115] = 1.0f;
	m_biomeColorsArray[116] = 1.0f;
	//---
	m_biomeColorsArray[117] = 1.0f;
	m_biomeColorsArray[118] = 1.0f;
	m_biomeColorsArray[119] = 1.0f;
	m_biomeColorsArray[120] = mountainsGrassColor.r;
	m_biomeColorsArray[121] = mountainsGrassColor.g;
	m_biomeColorsArray[122] = mountainsGrassColor.b;
	m_biomeColorsArray[123] = 1.0f;
	m_biomeColorsArray[124] = 1.0f;
	m_biomeColorsArray[125] = 1.0f;

	m_biomeColorsArray[126] = mountainsGrassColor.r;
	m_biomeColorsArray[127] = mountainsGrassColor.g;
	m_biomeColorsArray[128] = mountainsGrassColor.b;
	m_biomeColorsArray[129] = 1.0f;
	m_biomeColorsArray[130] = 1.0f;
	m_biomeColorsArray[131] = 1.0f;
	m_biomeColorsArray[132] = 1.0f;
	m_biomeColorsArray[133] = 1.0f;
	m_biomeColorsArray[134] = 1.0f;

	m_biomeColorsArray[135] = 1.0f;
	m_biomeColorsArray[136] = 1.0f;
	m_biomeColorsArray[137] = 1.0f;
	m_biomeColorsArray[138] = 1.0f;
	m_biomeColorsArray[139] = 1.0f;
	m_biomeColorsArray[140] = 1.0f;
	m_biomeColorsArray[141] = 1.0f;
	m_biomeColorsArray[142] = 1.0f;
	m_biomeColorsArray[143] = 1.0f;
	//---
	m_biomeColorsArray[144] = 1.0f;
	m_biomeColorsArray[145] = 1.0f;
	m_biomeColorsArray[146] = 1.0f;
	m_biomeColorsArray[147] = hillsGrassColor.r;
	m_biomeColorsArray[148] = hillsGrassColor.g;
	m_biomeColorsArray[149] = hillsGrassColor.b;
	m_biomeColorsArray[150] = 1.0f;
	m_biomeColorsArray[151] = 1.0f;
	m_biomeColorsArray[152] = 1.0f;

	m_biomeColorsArray[153] = hillsGrassColor.r;
	m_biomeColorsArray[154] = hillsGrassColor.g;
	m_biomeColorsArray[155] = hillsGrassColor.b;
	m_biomeColorsArray[156] = 1.0f;
	m_biomeColorsArray[157] = 1.0f;
	m_biomeColorsArray[158] = 1.0f;
	m_biomeColorsArray[159] = 1.0f;
	m_biomeColorsArray[160] = 1.0f;
	m_biomeColorsArray[161] = 1.0f;

	m_biomeColorsArray[162] = 1.0f;
	m_biomeColorsArray[163] = 1.0f;
	m_biomeColorsArray[164] = 1.0f;
	m_biomeColorsArray[165] = 1.0f;
	m_biomeColorsArray[166] = 1.0f;
	m_biomeColorsArray[167] = 1.0f;
	m_biomeColorsArray[168] = 1.0f;
	m_biomeColorsArray[169] = 1.0f;
	m_biomeColorsArray[170] = 1.0f;
	//---
	m_biomeColorsArray[171] = 1.0f;
	m_biomeColorsArray[172] = 1.0f;
	m_biomeColorsArray[173] = 1.0f;
	m_biomeColorsArray[174] = jungleGrassColor.r;
	m_biomeColorsArray[175] = jungleGrassColor.g;
	m_biomeColorsArray[176] = jungleGrassColor.b;
	m_biomeColorsArray[177] = 1.0f;
	m_biomeColorsArray[178] = 1.0f;
	m_biomeColorsArray[179] = 1.0f;

	m_biomeColorsArray[180] = jungleGrassColor.r;
	m_biomeColorsArray[181] = jungleGrassColor.g;
	m_biomeColorsArray[182] = jungleGrassColor.b;
	m_biomeColorsArray[183] = 1.0f;
	m_biomeColorsArray[184] = 1.0f;
	m_biomeColorsArray[185] = 1.0f;
	m_biomeColorsArray[186] = 1.0f;
	m_biomeColorsArray[187] = 1.0f;
	m_biomeColorsArray[188] = 1.0f;

	m_biomeColorsArray[189] = 1.0f;
	m_biomeColorsArray[190] = 1.0f;
	m_biomeColorsArray[191] = 1.0f;
	m_biomeColorsArray[192] = 1.0f;
	m_biomeColorsArray[193] = 1.0f;
	m_biomeColorsArray[194] = 1.0f;
	m_biomeColorsArray[195] = 1.0f;
	m_biomeColorsArray[196] = 1.0f;
	m_biomeColorsArray[197] = 1.0f;

	// SNOWY GRASS CUBE

	glm::vec3 taigaSnowyGrassColor = glm::pow(glm::vec3(0.525f, 0.717f, 0.513f), glm::vec3(2.2));
	glm::vec3 tundraSnowyGrassColor = glm::pow(glm::vec3(0.501f, 0.705f, 0.592f), glm::vec3(2.2));
	//--- TUNDRA
	m_biomeColorsArray[198] = 1.0f;
	m_biomeColorsArray[199] = 1.0f;
	m_biomeColorsArray[200] = 1.0f;
	m_biomeColorsArray[201] = 1.0f;
	m_biomeColorsArray[202] = 1.0f;
	m_biomeColorsArray[203] = 1.0f;
	m_biomeColorsArray[204] = 1.0f;
	m_biomeColorsArray[205] = 1.0f;
	m_biomeColorsArray[206] = 1.0f;

	m_biomeColorsArray[207] = tundraSnowyGrassColor.r;
	m_biomeColorsArray[208] = tundraSnowyGrassColor.g;
	m_biomeColorsArray[209] = tundraSnowyGrassColor.b;
	m_biomeColorsArray[210] = 1.0f;
	m_biomeColorsArray[211] = 1.0f;
	m_biomeColorsArray[212] = 1.0f;
	m_biomeColorsArray[213] = 1.0f;
	m_biomeColorsArray[214] = 1.0f;
	m_biomeColorsArray[215] = 1.0f;

	m_biomeColorsArray[216] = 1.0f;
	m_biomeColorsArray[217] = 1.0f;
	m_biomeColorsArray[218] = 1.0f;
	m_biomeColorsArray[219] = 1.0f;
	m_biomeColorsArray[220] = 1.0f;
	m_biomeColorsArray[221] = 1.0f;
	m_biomeColorsArray[222] = 1.0f;
	m_biomeColorsArray[223] = 1.0f;
	m_biomeColorsArray[224] = 1.0f;
	//--- TAIGA
	m_biomeColorsArray[225] = 1.0f;
	m_biomeColorsArray[226] = 1.0f;
	m_biomeColorsArray[227] = 1.0f;
	m_biomeColorsArray[228] = 1.0f;
	m_biomeColorsArray[229] = 1.0f;
	m_biomeColorsArray[230] = 1.0f;
	m_biomeColorsArray[231] = 1.0f;
	m_biomeColorsArray[232] = 1.0f;
	m_biomeColorsArray[233] = 1.0f;

	m_biomeColorsArray[234] = taigaSnowyGrassColor.r;
	m_biomeColorsArray[235] = taigaSnowyGrassColor.g;
	m_biomeColorsArray[236] = taigaSnowyGrassColor.b;
	m_biomeColorsArray[237] = 1.0f;
	m_biomeColorsArray[238] = 1.0f;
	m_biomeColorsArray[239] = 1.0f;
	m_biomeColorsArray[240] = 1.0f;
	m_biomeColorsArray[241] = 1.0f;
	m_biomeColorsArray[242] = 1.0f;

	m_biomeColorsArray[243] = 1.0f;
	m_biomeColorsArray[244] = 1.0f;
	m_biomeColorsArray[245] = 1.0f;
	m_biomeColorsArray[246] = 1.0f;
	m_biomeColorsArray[247] = 1.0f;
	m_biomeColorsArray[248] = 1.0f;
	m_biomeColorsArray[249] = 1.0f;
	m_biomeColorsArray[250] = 1.0f;
	m_biomeColorsArray[251] = 1.0f;
	//---

	// LEAVES

	glm::vec3 forestLeavesColor = glm::pow(glm::vec3(0.349f, 0.682f, 0.188f), glm::vec3(2.2));

	//--- FOREST
	m_biomeColorsArray[252] = forestLeavesColor.r;
	m_biomeColorsArray[253] = forestLeavesColor.g;
	m_biomeColorsArray[254] = forestLeavesColor.b;
	m_biomeColorsArray[255] = 1.0f;
	m_biomeColorsArray[256] = 1.0f;
	m_biomeColorsArray[257] = 1.0f;
	m_biomeColorsArray[258] = 1.0f;
	m_biomeColorsArray[259] = 1.0f;
	m_biomeColorsArray[260] = 1.0f;
	//---
}

BiomeColors::~BiomeColors() {
	delete[] m_biomeColorsArray;
}