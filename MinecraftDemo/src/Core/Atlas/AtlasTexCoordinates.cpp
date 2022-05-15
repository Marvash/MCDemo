#include "AtlasTexCoordinates.h"

AtlasTexCoordinates::AtlasTexCoordinates(unsigned int atlasWidth, unsigned int atlasHeight) : 
	m_atlasWidth(atlasWidth), 
	m_atlasHeight(atlasHeight) {
	m_atlasTexCoordinates = new GLfloat[TEX_COORDINATES_SIZE];

	// GRASS

	// SIDE
	// Top left
	m_atlasTexCoordinates[0] = getCoordX(12);
	m_atlasTexCoordinates[1] = getCoordX(13);
	m_atlasTexCoordinates[2] = -1.0f;
	m_atlasTexCoordinates[3] = getCoordY(10);
	m_atlasTexCoordinates[4] = getCoordY(10);
	m_atlasTexCoordinates[5] = -1.0f;
	// Top right
	m_atlasTexCoordinates[6] = getCoordX(13);
	m_atlasTexCoordinates[7] = getCoordX(14);
	m_atlasTexCoordinates[8] = -1.0f;
	m_atlasTexCoordinates[9] = getCoordY(10);
	m_atlasTexCoordinates[10] = getCoordY(10);
	m_atlasTexCoordinates[11] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[12] = getCoordX(13);
	m_atlasTexCoordinates[13] = getCoordX(14);
	m_atlasTexCoordinates[14] = -1.0f;
	m_atlasTexCoordinates[15] = getCoordY(11);
	m_atlasTexCoordinates[16] = getCoordY(11);
	m_atlasTexCoordinates[17] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[18] = getCoordX(12);
	m_atlasTexCoordinates[19] = getCoordX(13);
	m_atlasTexCoordinates[20] = -1.0f;
	m_atlasTexCoordinates[21] = getCoordY(11);
	m_atlasTexCoordinates[22] = getCoordY(11);
	m_atlasTexCoordinates[23] = -1.0f;

	// TOP
	// Top left
	m_atlasTexCoordinates[24] = getCoordX(15);
	m_atlasTexCoordinates[25] = -1.0f;
	m_atlasTexCoordinates[26] = -1.0f;
	m_atlasTexCoordinates[27] = getCoordY(10);
	m_atlasTexCoordinates[28] = -1.0f;
	m_atlasTexCoordinates[29] = -1.0f;
	// Top right
	m_atlasTexCoordinates[30] = getCoordX(16);
	m_atlasTexCoordinates[31] = -1.0f;
	m_atlasTexCoordinates[32] = -1.0f;
	m_atlasTexCoordinates[33] = getCoordY(10);
	m_atlasTexCoordinates[34] = -1.0f;
	m_atlasTexCoordinates[35] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[36] = getCoordX(16);
	m_atlasTexCoordinates[37] = -1.0f;
	m_atlasTexCoordinates[38] = -1.0f;
	m_atlasTexCoordinates[39] = getCoordY(11);
	m_atlasTexCoordinates[40] = -1.0f;
	m_atlasTexCoordinates[41] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[42] = getCoordX(15);
	m_atlasTexCoordinates[43] = -1.0f;
	m_atlasTexCoordinates[44] = -1.0f;
	m_atlasTexCoordinates[45] = getCoordY(11);
	m_atlasTexCoordinates[46] = -1.0f;
	m_atlasTexCoordinates[47] = -1.0f;

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[48] = getCoordX(8);
	m_atlasTexCoordinates[49] = -1.0f;
	m_atlasTexCoordinates[50] = -1.0f;
	m_atlasTexCoordinates[51] = getCoordY(6);
	m_atlasTexCoordinates[52] = -1.0f;
	m_atlasTexCoordinates[53] = -1.0f;
	// Top right
	m_atlasTexCoordinates[54] = getCoordX(9);
	m_atlasTexCoordinates[55] = -1.0f;
	m_atlasTexCoordinates[56] = -1.0f;
	m_atlasTexCoordinates[57] = getCoordY(6);
	m_atlasTexCoordinates[58] = -1.0f;
	m_atlasTexCoordinates[59] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[60] = getCoordX(9);
	m_atlasTexCoordinates[61] = -1.0f;
	m_atlasTexCoordinates[62] = -1.0f;
	m_atlasTexCoordinates[63] = getCoordY(7);
	m_atlasTexCoordinates[64] = -1.0f;
	m_atlasTexCoordinates[65] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[66] = getCoordX(8);
	m_atlasTexCoordinates[67] = -1.0f;
	m_atlasTexCoordinates[68] = -1.0f;
	m_atlasTexCoordinates[69] = getCoordY(7);
	m_atlasTexCoordinates[70] = -1.0f;
	m_atlasTexCoordinates[71] = -1.0f;

	// DIRT

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[72] = getCoordX(8);
	m_atlasTexCoordinates[73] = -1.0f;
	m_atlasTexCoordinates[74] = -1.0f;
	m_atlasTexCoordinates[75] = getCoordY(6);
	m_atlasTexCoordinates[76] = -1.0f;
	m_atlasTexCoordinates[77] = -1.0f;
	// Top right
	m_atlasTexCoordinates[78] = getCoordX(9);
	m_atlasTexCoordinates[79] = -1.0f;
	m_atlasTexCoordinates[80] = -1.0f;
	m_atlasTexCoordinates[81] = getCoordY(6);
	m_atlasTexCoordinates[82] = -1.0f;
	m_atlasTexCoordinates[83] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[84] = getCoordX(9);
	m_atlasTexCoordinates[85] = -1.0f;
	m_atlasTexCoordinates[86] = -1.0f;
	m_atlasTexCoordinates[87] = getCoordY(7);
	m_atlasTexCoordinates[88] = -1.0f;
	m_atlasTexCoordinates[89] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[90] = getCoordX(8);
	m_atlasTexCoordinates[91] = -1.0f;
	m_atlasTexCoordinates[92] = -1.0f;
	m_atlasTexCoordinates[93] = getCoordY(7);
	m_atlasTexCoordinates[94] = -1.0f;
	m_atlasTexCoordinates[95] = -1.0f;

	// STONE

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[96] = getCoordX(20);
	m_atlasTexCoordinates[97] = -1.0f;
	m_atlasTexCoordinates[98] = -1.0f;
	m_atlasTexCoordinates[99] = getCoordY(9);
	m_atlasTexCoordinates[100] = -1.0f;
	m_atlasTexCoordinates[101] = -1.0f;
	// Top right
	m_atlasTexCoordinates[102] = getCoordX(21);
	m_atlasTexCoordinates[103] = -1.0f;
	m_atlasTexCoordinates[104] = -1.0f;
	m_atlasTexCoordinates[105] = getCoordY(9);
	m_atlasTexCoordinates[106] = -1.0f;
	m_atlasTexCoordinates[107] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[108] = getCoordX(21);
	m_atlasTexCoordinates[109] = -1.0f;
	m_atlasTexCoordinates[110] = -1.0f;
	m_atlasTexCoordinates[111] = getCoordY(10);
	m_atlasTexCoordinates[112] = -1.0f;
	m_atlasTexCoordinates[113] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[114] = getCoordX(20);
	m_atlasTexCoordinates[115] = -1.0f;
	m_atlasTexCoordinates[116] = -1.0f;
	m_atlasTexCoordinates[117] = getCoordY(10);
	m_atlasTexCoordinates[118] = -1.0f;
	m_atlasTexCoordinates[119] = -1.0f;

	// SAND

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[120] = getCoordX(19);
	m_atlasTexCoordinates[121] = -1.0f;
	m_atlasTexCoordinates[122] = -1.0f;
	m_atlasTexCoordinates[123] = getCoordY(7);
	m_atlasTexCoordinates[124] = -1.0f;
	m_atlasTexCoordinates[125] = -1.0f;
	// Top right
	m_atlasTexCoordinates[126] = getCoordX(20);
	m_atlasTexCoordinates[127] = -1.0f;
	m_atlasTexCoordinates[128] = -1.0f;
	m_atlasTexCoordinates[129] = getCoordY(7);
	m_atlasTexCoordinates[130] = -1.0f;
	m_atlasTexCoordinates[131] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[132] = getCoordX(20);
	m_atlasTexCoordinates[133] = -1.0f;
	m_atlasTexCoordinates[134] = -1.0f;
	m_atlasTexCoordinates[135] = getCoordY(8);
	m_atlasTexCoordinates[136] = -1.0f;
	m_atlasTexCoordinates[137] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[138] = getCoordX(19);
	m_atlasTexCoordinates[139] = -1.0f;
	m_atlasTexCoordinates[140] = -1.0f;
	m_atlasTexCoordinates[141] = getCoordY(8);
	m_atlasTexCoordinates[142] = -1.0f;
	m_atlasTexCoordinates[143] = -1.0f;

	// SNOWY GRASS

	// SIDE
	// Top left
	m_atlasTexCoordinates[144] = getCoordX(14);
	m_atlasTexCoordinates[145] = -1.0f;
	m_atlasTexCoordinates[146] = -1.0f;
	m_atlasTexCoordinates[147] = getCoordY(10);
	m_atlasTexCoordinates[148] = -1.0f;
	m_atlasTexCoordinates[149] = -1.0f;
	// Top right
	m_atlasTexCoordinates[150] = getCoordX(15);
	m_atlasTexCoordinates[151] = -1.0f;
	m_atlasTexCoordinates[152] = -1.0f;
	m_atlasTexCoordinates[153] = getCoordY(10);
	m_atlasTexCoordinates[154] = -1.0f;
	m_atlasTexCoordinates[155] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[156] = getCoordX(15);
	m_atlasTexCoordinates[157] = -1.0f;
	m_atlasTexCoordinates[158] = -1.0f;
	m_atlasTexCoordinates[159] = getCoordY(11);
	m_atlasTexCoordinates[160] = -1.0f;
	m_atlasTexCoordinates[161] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[162] = getCoordX(14);
	m_atlasTexCoordinates[163] = -1.0f;
	m_atlasTexCoordinates[164] = -1.0f;
	m_atlasTexCoordinates[165] = getCoordY(11);
	m_atlasTexCoordinates[166] = -1.0f;
	m_atlasTexCoordinates[167] = -1.0f;

	// TOP
	// Top left
	m_atlasTexCoordinates[168] = getCoordX(15);
	m_atlasTexCoordinates[169] = -1.0f;
	m_atlasTexCoordinates[170] = -1.0f;
	m_atlasTexCoordinates[171] = getCoordY(10);
	m_atlasTexCoordinates[172] = -1.0f;
	m_atlasTexCoordinates[173] = -1.0f;
	// Top right
	m_atlasTexCoordinates[174] = getCoordX(16);
	m_atlasTexCoordinates[175] = -1.0f;
	m_atlasTexCoordinates[176] = -1.0f;
	m_atlasTexCoordinates[177] = getCoordY(10);
	m_atlasTexCoordinates[178] = -1.0f;
	m_atlasTexCoordinates[179] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[180] = getCoordX(16);
	m_atlasTexCoordinates[181] = -1.0f;
	m_atlasTexCoordinates[182] = -1.0f;
	m_atlasTexCoordinates[183] = getCoordY(11);
	m_atlasTexCoordinates[184] = -1.0f;
	m_atlasTexCoordinates[185] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[186] = getCoordX(15);
	m_atlasTexCoordinates[187] = -1.0f;
	m_atlasTexCoordinates[188] = -1.0f;
	m_atlasTexCoordinates[189] = getCoordY(11);
	m_atlasTexCoordinates[190] = -1.0f;
	m_atlasTexCoordinates[191] = -1.0f;

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[192] = getCoordX(8);
	m_atlasTexCoordinates[193] = -1.0f;
	m_atlasTexCoordinates[194] = -1.0f;
	m_atlasTexCoordinates[195] = getCoordY(6);
	m_atlasTexCoordinates[196] = -1.0f;
	m_atlasTexCoordinates[197] = -1.0f;
	// Top right
	m_atlasTexCoordinates[198] = getCoordX(9);
	m_atlasTexCoordinates[199] = -1.0f;
	m_atlasTexCoordinates[200] = -1.0f;
	m_atlasTexCoordinates[201] = getCoordY(6);
	m_atlasTexCoordinates[202] = -1.0f;
	m_atlasTexCoordinates[203] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[204] = getCoordX(9);
	m_atlasTexCoordinates[205] = -1.0f;
	m_atlasTexCoordinates[206] = -1.0f;
	m_atlasTexCoordinates[207] = getCoordY(7);
	m_atlasTexCoordinates[208] = -1.0f;
	m_atlasTexCoordinates[209] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[210] = getCoordX(8);
	m_atlasTexCoordinates[211] = -1.0f;
	m_atlasTexCoordinates[212] = -1.0f;
	m_atlasTexCoordinates[213] = getCoordY(7);
	m_atlasTexCoordinates[214] = -1.0f;
	m_atlasTexCoordinates[215] = -1.0f;

	// OAK LOG

	// SIDE
	// Top left
	m_atlasTexCoordinates[216] = getCoordX(3);
	m_atlasTexCoordinates[217] = -1.0f;
	m_atlasTexCoordinates[218] = -1.0f;
	m_atlasTexCoordinates[219] = getCoordY(14);
	m_atlasTexCoordinates[220] = -1.0f;
	m_atlasTexCoordinates[221] = -1.0f;
	// Top right
	m_atlasTexCoordinates[222] = getCoordX(4);
	m_atlasTexCoordinates[223] = -1.0f;
	m_atlasTexCoordinates[224] = -1.0f;
	m_atlasTexCoordinates[225] = getCoordY(14);
	m_atlasTexCoordinates[226] = -1.0f;
	m_atlasTexCoordinates[227] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[228] = getCoordX(4);
	m_atlasTexCoordinates[229] = -1.0f;
	m_atlasTexCoordinates[230] = -1.0f;
	m_atlasTexCoordinates[231] = getCoordY(15);
	m_atlasTexCoordinates[232] = -1.0f;
	m_atlasTexCoordinates[233] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[234] = getCoordX(3);
	m_atlasTexCoordinates[235] = -1.0f;
	m_atlasTexCoordinates[236] = -1.0f;
	m_atlasTexCoordinates[237] = getCoordY(15);
	m_atlasTexCoordinates[238] = -1.0f;
	m_atlasTexCoordinates[239] = -1.0f;

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[240] = getCoordX(4);
	m_atlasTexCoordinates[241] = -1.0f;
	m_atlasTexCoordinates[242] = -1.0f;
	m_atlasTexCoordinates[243] = getCoordY(14);
	m_atlasTexCoordinates[244] = -1.0f;
	m_atlasTexCoordinates[245] = -1.0f;
	// Top right
	m_atlasTexCoordinates[246] = getCoordX(5);
	m_atlasTexCoordinates[247] = -1.0f;
	m_atlasTexCoordinates[248] = -1.0f;
	m_atlasTexCoordinates[249] = getCoordY(14);
	m_atlasTexCoordinates[250] = -1.0f;
	m_atlasTexCoordinates[251] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[252] = getCoordX(5);
	m_atlasTexCoordinates[253] = -1.0f;
	m_atlasTexCoordinates[254] = -1.0f;
	m_atlasTexCoordinates[255] = getCoordY(15);
	m_atlasTexCoordinates[256] = -1.0f;
	m_atlasTexCoordinates[257] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[258] = getCoordX(4);
	m_atlasTexCoordinates[259] = -1.0f;
	m_atlasTexCoordinates[260] = -1.0f;
	m_atlasTexCoordinates[261] = getCoordY(15);
	m_atlasTexCoordinates[262] = -1.0f;
	m_atlasTexCoordinates[263] = -1.0f;

	// LEAVES

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[264] = getCoordX(4);
	m_atlasTexCoordinates[265] = -1.0f;
	m_atlasTexCoordinates[266] = -1.0f;
	m_atlasTexCoordinates[267] = getCoordY(13);
	m_atlasTexCoordinates[268] = -1.0f;
	m_atlasTexCoordinates[269] = -1.0f;
	// Top right
	m_atlasTexCoordinates[270] = getCoordX(5);
	m_atlasTexCoordinates[271] = -1.0f;
	m_atlasTexCoordinates[272] = -1.0f;
	m_atlasTexCoordinates[273] = getCoordY(13);
	m_atlasTexCoordinates[274] = -1.0f;
	m_atlasTexCoordinates[275] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[276] = getCoordX(5);
	m_atlasTexCoordinates[277] = -1.0f;
	m_atlasTexCoordinates[278] = -1.0f;
	m_atlasTexCoordinates[279] = getCoordY(14);
	m_atlasTexCoordinates[280] = -1.0f;
	m_atlasTexCoordinates[281] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[282] = getCoordX(4);
	m_atlasTexCoordinates[283] = -1.0f;
	m_atlasTexCoordinates[284] = -1.0f;
	m_atlasTexCoordinates[285] = getCoordY(14);
	m_atlasTexCoordinates[286] = -1.0f;
	m_atlasTexCoordinates[287] = -1.0f;
}

AtlasTexCoordinates::~AtlasTexCoordinates() {
	delete[] m_atlasTexCoordinates;
}

//Gets sprite texCoords starting from left
float AtlasTexCoordinates::getCoordX(int spriteNum) {
	float spriteWidth = m_atlasWidth / NUM_SPRITES_X;
	return (spriteWidth * spriteNum) / m_atlasWidth;
}

//Gets sprite texCoords starting from top
float AtlasTexCoordinates::getCoordY(int spriteNum) {
	float spriteHeight = (m_atlasHeight / NUM_SPRITES_Y);
	return 1.0f - ((spriteHeight * spriteNum) / m_atlasHeight);
}