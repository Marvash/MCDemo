#include "AtlasTexCoordinates.h"

AtlasTexCoordinates::AtlasTexCoordinates(unsigned int atlasWidth, unsigned int atlasHeight) :
	m_atlasWidth(atlasWidth),
	m_atlasHeight(atlasHeight) {
	m_atlasTexCoordinates = new GLfloat[TEX_COORDINATES_SIZE];
	m_atlasSecondaryTexCoordinates = new GLfloat[SECONDARY_TEX_COORDINATES_SIZE];

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

	// PLANK

	// BOTTOM
	// Top left
	m_atlasTexCoordinates[288] = getCoordX(16);
	m_atlasTexCoordinates[289] = -1.0f;
	m_atlasTexCoordinates[290] = -1.0f;
	m_atlasTexCoordinates[291] = getCoordY(4);
	m_atlasTexCoordinates[292] = -1.0f;
	m_atlasTexCoordinates[293] = -1.0f;
	// Top right
	m_atlasTexCoordinates[294] = getCoordX(17);
	m_atlasTexCoordinates[295] = -1.0f;
	m_atlasTexCoordinates[296] = -1.0f;
	m_atlasTexCoordinates[297] = getCoordY(4);
	m_atlasTexCoordinates[298] = -1.0f;
	m_atlasTexCoordinates[299] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[300] = getCoordX(17);
	m_atlasTexCoordinates[301] = -1.0f;
	m_atlasTexCoordinates[302] = -1.0f;
	m_atlasTexCoordinates[303] = getCoordY(5);
	m_atlasTexCoordinates[304] = -1.0f;
	m_atlasTexCoordinates[305] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[306] = getCoordX(16);
	m_atlasTexCoordinates[307] = -1.0f;
	m_atlasTexCoordinates[308] = -1.0f;
	m_atlasTexCoordinates[309] = getCoordY(5);
	m_atlasTexCoordinates[310] = -1.0f;
	m_atlasTexCoordinates[311] = -1.0f;

	// STICK

	// Top left
	m_atlasTexCoordinates[312] = getCoordX(10);
	m_atlasTexCoordinates[313] = -1.0f;
	m_atlasTexCoordinates[314] = -1.0f;
	m_atlasTexCoordinates[315] = getCoordY(18);
	m_atlasTexCoordinates[316] = -1.0f;
	m_atlasTexCoordinates[317] = -1.0f;
	// Top right
	m_atlasTexCoordinates[318] = getCoordX(11);
	m_atlasTexCoordinates[319] = -1.0f;
	m_atlasTexCoordinates[320] = -1.0f;
	m_atlasTexCoordinates[321] = getCoordY(18);
	m_atlasTexCoordinates[322] = -1.0f;
	m_atlasTexCoordinates[323] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[324] = getCoordX(11);
	m_atlasTexCoordinates[325] = -1.0f;
	m_atlasTexCoordinates[326] = -1.0f;
	m_atlasTexCoordinates[327] = getCoordY(19);
	m_atlasTexCoordinates[328] = -1.0f;
	m_atlasTexCoordinates[329] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[330] = getCoordX(10);
	m_atlasTexCoordinates[331] = -1.0f;
	m_atlasTexCoordinates[332] = -1.0f;
	m_atlasTexCoordinates[333] = getCoordY(19);
	m_atlasTexCoordinates[334] = -1.0f;
	m_atlasTexCoordinates[335] = -1.0f;

	// WOODEN AXE

	// Top left
	m_atlasTexCoordinates[336] = getCoordX(19);
	m_atlasTexCoordinates[337] = -1.0f;
	m_atlasTexCoordinates[338] = -1.0f;
	m_atlasTexCoordinates[339] = getCoordY(18);
	m_atlasTexCoordinates[340] = -1.0f;
	m_atlasTexCoordinates[341] = -1.0f;
	// Top right
	m_atlasTexCoordinates[342] = getCoordX(20);
	m_atlasTexCoordinates[343] = -1.0f;
	m_atlasTexCoordinates[344] = -1.0f;
	m_atlasTexCoordinates[345] = getCoordY(18);
	m_atlasTexCoordinates[346] = -1.0f;
	m_atlasTexCoordinates[347] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[348] = getCoordX(20);
	m_atlasTexCoordinates[349] = -1.0f;
	m_atlasTexCoordinates[350] = -1.0f;
	m_atlasTexCoordinates[351] = getCoordY(19);
	m_atlasTexCoordinates[352] = -1.0f;
	m_atlasTexCoordinates[353] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[354] = getCoordX(19);
	m_atlasTexCoordinates[355] = -1.0f;
	m_atlasTexCoordinates[356] = -1.0f;
	m_atlasTexCoordinates[357] = getCoordY(19);
	m_atlasTexCoordinates[358] = -1.0f;
	m_atlasTexCoordinates[359] = -1.0f;

	// WOODEN HOE

	// Top left
	m_atlasTexCoordinates[360] = getCoordX(20);
	m_atlasTexCoordinates[361] = -1.0f;
	m_atlasTexCoordinates[362] = -1.0f;
	m_atlasTexCoordinates[363] = getCoordY(18);
	m_atlasTexCoordinates[364] = -1.0f;
	m_atlasTexCoordinates[365] = -1.0f;
	// Top right
	m_atlasTexCoordinates[366] = getCoordX(21);
	m_atlasTexCoordinates[367] = -1.0f;
	m_atlasTexCoordinates[368] = -1.0f;
	m_atlasTexCoordinates[369] = getCoordY(18);
	m_atlasTexCoordinates[370] = -1.0f;
	m_atlasTexCoordinates[371] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[372] = getCoordX(21);
	m_atlasTexCoordinates[373] = -1.0f;
	m_atlasTexCoordinates[374] = -1.0f;
	m_atlasTexCoordinates[375] = getCoordY(19);
	m_atlasTexCoordinates[376] = -1.0f;
	m_atlasTexCoordinates[377] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[378] = getCoordX(20);
	m_atlasTexCoordinates[379] = -1.0f;
	m_atlasTexCoordinates[380] = -1.0f;
	m_atlasTexCoordinates[381] = getCoordY(19);
	m_atlasTexCoordinates[382] = -1.0f;
	m_atlasTexCoordinates[383] = -1.0f;

	// WOODEN PICKAXE

	// Top left
	m_atlasTexCoordinates[384] = getCoordX(21);
	m_atlasTexCoordinates[385] = -1.0f;
	m_atlasTexCoordinates[386] = -1.0f;
	m_atlasTexCoordinates[387] = getCoordY(18);
	m_atlasTexCoordinates[388] = -1.0f;
	m_atlasTexCoordinates[389] = -1.0f;
	// Top right
	m_atlasTexCoordinates[390] = getCoordX(22);
	m_atlasTexCoordinates[391] = -1.0f;
	m_atlasTexCoordinates[392] = -1.0f;
	m_atlasTexCoordinates[393] = getCoordY(18);
	m_atlasTexCoordinates[394] = -1.0f;
	m_atlasTexCoordinates[395] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[396] = getCoordX(22);
	m_atlasTexCoordinates[397] = -1.0f;
	m_atlasTexCoordinates[398] = -1.0f;
	m_atlasTexCoordinates[399] = getCoordY(19);
	m_atlasTexCoordinates[400] = -1.0f;
	m_atlasTexCoordinates[401] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[402] = getCoordX(21);
	m_atlasTexCoordinates[403] = -1.0f;
	m_atlasTexCoordinates[404] = -1.0f;
	m_atlasTexCoordinates[405] = getCoordY(19);
	m_atlasTexCoordinates[406] = -1.0f;
	m_atlasTexCoordinates[407] = -1.0f;

	// WOODEN SHOVEL

	// Top left
	m_atlasTexCoordinates[408] = getCoordX(22);
	m_atlasTexCoordinates[409] = -1.0f;
	m_atlasTexCoordinates[410] = -1.0f;
	m_atlasTexCoordinates[411] = getCoordY(18);
	m_atlasTexCoordinates[412] = -1.0f;
	m_atlasTexCoordinates[413] = -1.0f;
	// Top right
	m_atlasTexCoordinates[414] = getCoordX(23);
	m_atlasTexCoordinates[415] = -1.0f;
	m_atlasTexCoordinates[416] = -1.0f;
	m_atlasTexCoordinates[417] = getCoordY(18);
	m_atlasTexCoordinates[418] = -1.0f;
	m_atlasTexCoordinates[419] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[420] = getCoordX(23);
	m_atlasTexCoordinates[421] = -1.0f;
	m_atlasTexCoordinates[422] = -1.0f;
	m_atlasTexCoordinates[423] = getCoordY(19);
	m_atlasTexCoordinates[424] = -1.0f;
	m_atlasTexCoordinates[425] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[426] = getCoordX(22);
	m_atlasTexCoordinates[427] = -1.0f;
	m_atlasTexCoordinates[428] = -1.0f;
	m_atlasTexCoordinates[429] = getCoordY(19);
	m_atlasTexCoordinates[430] = -1.0f;
	m_atlasTexCoordinates[431] = -1.0f;

	// WOODEN SWORD

	// Top left
	m_atlasTexCoordinates[432] = getCoordX(23);
	m_atlasTexCoordinates[433] = -1.0f;
	m_atlasTexCoordinates[434] = -1.0f;
	m_atlasTexCoordinates[435] = getCoordY(18);
	m_atlasTexCoordinates[436] = -1.0f;
	m_atlasTexCoordinates[437] = -1.0f;
	// Top right
	m_atlasTexCoordinates[438] = getCoordX(24);
	m_atlasTexCoordinates[439] = -1.0f;
	m_atlasTexCoordinates[440] = -1.0f;
	m_atlasTexCoordinates[441] = getCoordY(18);
	m_atlasTexCoordinates[442] = -1.0f;
	m_atlasTexCoordinates[443] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[444] = getCoordX(24);
	m_atlasTexCoordinates[445] = -1.0f;
	m_atlasTexCoordinates[446] = -1.0f;
	m_atlasTexCoordinates[447] = getCoordY(19);
	m_atlasTexCoordinates[448] = -1.0f;
	m_atlasTexCoordinates[449] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[450] = getCoordX(23);
	m_atlasTexCoordinates[451] = -1.0f;
	m_atlasTexCoordinates[452] = -1.0f;
	m_atlasTexCoordinates[453] = getCoordY(19);
	m_atlasTexCoordinates[454] = -1.0f;
	m_atlasTexCoordinates[455] = -1.0f;

	// STONE AXE

	// Top left
	m_atlasTexCoordinates[456] = getCoordX(11);
	m_atlasTexCoordinates[457] = -1.0f;
	m_atlasTexCoordinates[458] = -1.0f;
	m_atlasTexCoordinates[459] = getCoordY(18);
	m_atlasTexCoordinates[460] = -1.0f;
	m_atlasTexCoordinates[461] = -1.0f;
	// Top right
	m_atlasTexCoordinates[462] = getCoordX(12);
	m_atlasTexCoordinates[463] = -1.0f;
	m_atlasTexCoordinates[464] = -1.0f;
	m_atlasTexCoordinates[465] = getCoordY(18);
	m_atlasTexCoordinates[466] = -1.0f;
	m_atlasTexCoordinates[467] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[468] = getCoordX(12);
	m_atlasTexCoordinates[469] = -1.0f;
	m_atlasTexCoordinates[470] = -1.0f;
	m_atlasTexCoordinates[471] = getCoordY(19);
	m_atlasTexCoordinates[472] = -1.0f;
	m_atlasTexCoordinates[473] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[474] = getCoordX(11);
	m_atlasTexCoordinates[475] = -1.0f;
	m_atlasTexCoordinates[476] = -1.0f;
	m_atlasTexCoordinates[477] = getCoordY(19);
	m_atlasTexCoordinates[478] = -1.0f;
	m_atlasTexCoordinates[479] = -1.0f;

	// STONE HOE

	// Top left
	m_atlasTexCoordinates[480] = getCoordX(12);
	m_atlasTexCoordinates[481] = -1.0f;
	m_atlasTexCoordinates[482] = -1.0f;
	m_atlasTexCoordinates[483] = getCoordY(18);
	m_atlasTexCoordinates[484] = -1.0f;
	m_atlasTexCoordinates[485] = -1.0f;
	// Top right
	m_atlasTexCoordinates[486] = getCoordX(13);
	m_atlasTexCoordinates[487] = -1.0f;
	m_atlasTexCoordinates[488] = -1.0f;
	m_atlasTexCoordinates[489] = getCoordY(18);
	m_atlasTexCoordinates[490] = -1.0f;
	m_atlasTexCoordinates[491] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[492] = getCoordX(13);
	m_atlasTexCoordinates[493] = -1.0f;
	m_atlasTexCoordinates[494] = -1.0f;
	m_atlasTexCoordinates[495] = getCoordY(19);
	m_atlasTexCoordinates[496] = -1.0f;
	m_atlasTexCoordinates[497] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[498] = getCoordX(12);
	m_atlasTexCoordinates[499] = -1.0f;
	m_atlasTexCoordinates[500] = -1.0f;
	m_atlasTexCoordinates[501] = getCoordY(19);
	m_atlasTexCoordinates[502] = -1.0f;
	m_atlasTexCoordinates[503] = -1.0f;

	// STONE PICKAXE

	// Top left
	m_atlasTexCoordinates[504] = getCoordX(13);
	m_atlasTexCoordinates[505] = -1.0f;
	m_atlasTexCoordinates[506] = -1.0f;
	m_atlasTexCoordinates[507] = getCoordY(18);
	m_atlasTexCoordinates[508] = -1.0f;
	m_atlasTexCoordinates[509] = -1.0f;
	// Top right
	m_atlasTexCoordinates[510] = getCoordX(14);
	m_atlasTexCoordinates[511] = -1.0f;
	m_atlasTexCoordinates[512] = -1.0f;
	m_atlasTexCoordinates[513] = getCoordY(18);
	m_atlasTexCoordinates[514] = -1.0f;
	m_atlasTexCoordinates[515] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[516] = getCoordX(14);
	m_atlasTexCoordinates[517] = -1.0f;
	m_atlasTexCoordinates[518] = -1.0f;
	m_atlasTexCoordinates[519] = getCoordY(19);
	m_atlasTexCoordinates[520] = -1.0f;
	m_atlasTexCoordinates[521] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[522] = getCoordX(13);
	m_atlasTexCoordinates[523] = -1.0f;
	m_atlasTexCoordinates[524] = -1.0f;
	m_atlasTexCoordinates[525] = getCoordY(19);
	m_atlasTexCoordinates[526] = -1.0f;
	m_atlasTexCoordinates[527] = -1.0f;

	// STONE SHOVEL

	// Top left
	m_atlasTexCoordinates[528] = getCoordX(14);
	m_atlasTexCoordinates[529] = -1.0f;
	m_atlasTexCoordinates[530] = -1.0f;
	m_atlasTexCoordinates[531] = getCoordY(18);
	m_atlasTexCoordinates[532] = -1.0f;
	m_atlasTexCoordinates[533] = -1.0f;
	// Top right
	m_atlasTexCoordinates[534] = getCoordX(15);
	m_atlasTexCoordinates[535] = -1.0f;
	m_atlasTexCoordinates[536] = -1.0f;
	m_atlasTexCoordinates[537] = getCoordY(18);
	m_atlasTexCoordinates[538] = -1.0f;
	m_atlasTexCoordinates[539] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[540] = getCoordX(15);
	m_atlasTexCoordinates[541] = -1.0f;
	m_atlasTexCoordinates[542] = -1.0f;
	m_atlasTexCoordinates[543] = getCoordY(19);
	m_atlasTexCoordinates[544] = -1.0f;
	m_atlasTexCoordinates[545] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[546] = getCoordX(14);
	m_atlasTexCoordinates[547] = -1.0f;
	m_atlasTexCoordinates[548] = -1.0f;
	m_atlasTexCoordinates[549] = getCoordY(19);
	m_atlasTexCoordinates[550] = -1.0f;
	m_atlasTexCoordinates[551] = -1.0f;

	// STONE SWORD

	// Top left
	m_atlasTexCoordinates[552] = getCoordX(15);
	m_atlasTexCoordinates[553] = -1.0f;
	m_atlasTexCoordinates[554] = -1.0f;
	m_atlasTexCoordinates[555] = getCoordY(18);
	m_atlasTexCoordinates[556] = -1.0f;
	m_atlasTexCoordinates[557] = -1.0f;
	// Top right
	m_atlasTexCoordinates[558] = getCoordX(16);
	m_atlasTexCoordinates[559] = -1.0f;
	m_atlasTexCoordinates[560] = -1.0f;
	m_atlasTexCoordinates[561] = getCoordY(18);
	m_atlasTexCoordinates[562] = -1.0f;
	m_atlasTexCoordinates[563] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[564] = getCoordX(16);
	m_atlasTexCoordinates[565] = -1.0f;
	m_atlasTexCoordinates[566] = -1.0f;
	m_atlasTexCoordinates[567] = getCoordY(19);
	m_atlasTexCoordinates[568] = -1.0f;
	m_atlasTexCoordinates[569] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[570] = getCoordX(15);
	m_atlasTexCoordinates[571] = -1.0f;
	m_atlasTexCoordinates[572] = -1.0f;
	m_atlasTexCoordinates[573] = getCoordY(19);
	m_atlasTexCoordinates[574] = -1.0f;
	m_atlasTexCoordinates[575] = -1.0f;

	// UNKNOWN ITEM

	// Top left
	m_atlasTexCoordinates[576] = getCoordX(25);
	m_atlasTexCoordinates[577] = -1.0f;
	m_atlasTexCoordinates[578] = -1.0f;
	m_atlasTexCoordinates[579] = getCoordY(18);
	m_atlasTexCoordinates[580] = -1.0f;
	m_atlasTexCoordinates[581] = -1.0f;
	// Top right
	m_atlasTexCoordinates[582] = getCoordX(26);
	m_atlasTexCoordinates[583] = -1.0f;
	m_atlasTexCoordinates[584] = -1.0f;
	m_atlasTexCoordinates[585] = getCoordY(18);
	m_atlasTexCoordinates[586] = -1.0f;
	m_atlasTexCoordinates[587] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[588] = getCoordX(26);
	m_atlasTexCoordinates[589] = -1.0f;
	m_atlasTexCoordinates[590] = -1.0f;
	m_atlasTexCoordinates[591] = getCoordY(19);
	m_atlasTexCoordinates[592] = -1.0f;
	m_atlasTexCoordinates[593] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[594] = getCoordX(25);
	m_atlasTexCoordinates[595] = -1.0f;
	m_atlasTexCoordinates[596] = -1.0f;
	m_atlasTexCoordinates[597] = getCoordY(19);
	m_atlasTexCoordinates[598] = -1.0f;
	m_atlasTexCoordinates[599] = -1.0f;

	// COBBLESTONE 

	// Top left
	m_atlasTexCoordinates[600] = getCoordX(3);
	m_atlasTexCoordinates[601] = -1.0f;
	m_atlasTexCoordinates[602] = -1.0f;
	m_atlasTexCoordinates[603] = getCoordY(5);
	m_atlasTexCoordinates[604] = -1.0f;
	m_atlasTexCoordinates[605] = -1.0f;
	// Top right
	m_atlasTexCoordinates[606] = getCoordX(4);
	m_atlasTexCoordinates[607] = -1.0f;
	m_atlasTexCoordinates[608] = -1.0f;
	m_atlasTexCoordinates[609] = getCoordY(5);
	m_atlasTexCoordinates[610] = -1.0f;
	m_atlasTexCoordinates[611] = -1.0f;
	// Bottom right
	m_atlasTexCoordinates[612] = getCoordX(4);
	m_atlasTexCoordinates[613] = -1.0f;
	m_atlasTexCoordinates[614] = -1.0f;
	m_atlasTexCoordinates[615] = getCoordY(6);
	m_atlasTexCoordinates[616] = -1.0f;
	m_atlasTexCoordinates[617] = -1.0f;
	// Bottom left
	m_atlasTexCoordinates[618] = getCoordX(3);
	m_atlasTexCoordinates[619] = -1.0f;
	m_atlasTexCoordinates[620] = -1.0f;
	m_atlasTexCoordinates[621] = getCoordY(6);
	m_atlasTexCoordinates[622] = -1.0f;
	m_atlasTexCoordinates[623] = -1.0f;


	// SECONDARY TEX COORDINATES
	// BLOCK BREAK TEXTURE 1

	// Top left
	m_atlasSecondaryTexCoordinates[0] = getCoordX(2);
	m_atlasSecondaryTexCoordinates[1] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[2] = getCoordX(3);
	m_atlasSecondaryTexCoordinates[3] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[4] = getCoordX(3);
	m_atlasSecondaryTexCoordinates[5] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[6] = getCoordX(2);
	m_atlasSecondaryTexCoordinates[7] = getCoordY(8);

	// BLOCK BREAK TEXTURE 2

	// Top left
	m_atlasSecondaryTexCoordinates[8] = getCoordX(3);
	m_atlasSecondaryTexCoordinates[9] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[10] = getCoordX(4);
	m_atlasSecondaryTexCoordinates[11] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[12] = getCoordX(4);
	m_atlasSecondaryTexCoordinates[13] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[14] = getCoordX(3);
	m_atlasSecondaryTexCoordinates[15] = getCoordY(8);

	// BLOCK BREAK TEXTURE 3

	// Top left
	m_atlasSecondaryTexCoordinates[16] = getCoordX(4);
	m_atlasSecondaryTexCoordinates[17] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[18] = getCoordX(5);
	m_atlasSecondaryTexCoordinates[19] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[20] = getCoordX(5);
	m_atlasSecondaryTexCoordinates[21] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[22] = getCoordX(4);
	m_atlasSecondaryTexCoordinates[23] = getCoordY(8);

	// BLOCK BREAK TEXTURE 4

	// Top left
	m_atlasSecondaryTexCoordinates[24] = getCoordX(5);
	m_atlasSecondaryTexCoordinates[25] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[26] = getCoordX(6);
	m_atlasSecondaryTexCoordinates[27] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[28] = getCoordX(6);
	m_atlasSecondaryTexCoordinates[29] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[30] = getCoordX(5);
	m_atlasSecondaryTexCoordinates[31] = getCoordY(8);

	// BLOCK BREAK TEXTURE 5

	// Top left
	m_atlasSecondaryTexCoordinates[32] = getCoordX(6);
	m_atlasSecondaryTexCoordinates[33] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[34] = getCoordX(7);
	m_atlasSecondaryTexCoordinates[35] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[36] = getCoordX(7);
	m_atlasSecondaryTexCoordinates[37] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[38] = getCoordX(6);
	m_atlasSecondaryTexCoordinates[39] = getCoordY(8);

	// BLOCK BREAK TEXTURE 6

	// Top left
	m_atlasSecondaryTexCoordinates[40] = getCoordX(7);
	m_atlasSecondaryTexCoordinates[41] = getCoordY(7);
	// Top right
	m_atlasSecondaryTexCoordinates[42] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[43] = getCoordY(7);
	// Bottom right
	m_atlasSecondaryTexCoordinates[44] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[45] = getCoordY(8);
	// Bottom left
	m_atlasSecondaryTexCoordinates[46] = getCoordX(7);
	m_atlasSecondaryTexCoordinates[47] = getCoordY(8);

	// BLOCK BREAK TEXTURE 7

	// Top left
	m_atlasSecondaryTexCoordinates[48] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[49] = getCoordY(0);
	// Top right
	m_atlasSecondaryTexCoordinates[50] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[51] = getCoordY(0);
	// Bottom right
	m_atlasSecondaryTexCoordinates[52] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[53] = getCoordY(1);
	// Bottom left
	m_atlasSecondaryTexCoordinates[54] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[55] = getCoordY(1);

	// BLOCK BREAK TEXTURE 8

	// Top left
	m_atlasSecondaryTexCoordinates[56] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[57] = getCoordY(1);
	// Top right
	m_atlasSecondaryTexCoordinates[58] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[59] = getCoordY(1);
	// Bottom right
	m_atlasSecondaryTexCoordinates[60] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[61] = getCoordY(2);
	// Bottom left
	m_atlasSecondaryTexCoordinates[62] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[63] = getCoordY(2);

	// BLOCK BREAK TEXTURE 9

	// Top left
	m_atlasSecondaryTexCoordinates[64] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[65] = getCoordY(2);
	// Top right
	m_atlasSecondaryTexCoordinates[66] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[67] = getCoordY(2);
	// Bottom right
	m_atlasSecondaryTexCoordinates[68] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[69] = getCoordY(3);
	// Bottom left
	m_atlasSecondaryTexCoordinates[70] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[71] = getCoordY(3);

	// BLOCK BREAK TEXTURE 10

	// Top left
	m_atlasSecondaryTexCoordinates[72] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[73] = getCoordY(3);
	// Top right
	m_atlasSecondaryTexCoordinates[74] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[75] = getCoordY(3);
	// Bottom right
	m_atlasSecondaryTexCoordinates[76] = getCoordX(9);
	m_atlasSecondaryTexCoordinates[77] = getCoordY(4);
	// Bottom left
	m_atlasSecondaryTexCoordinates[78] = getCoordX(8);
	m_atlasSecondaryTexCoordinates[79] = getCoordY(4);
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