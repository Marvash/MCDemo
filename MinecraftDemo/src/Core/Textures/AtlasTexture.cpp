#include "AtlasTexture.h"

AtlasTexture::AtlasTexture(std::vector<std::string>& atlasMipPaths) :
	Texture(GL_TEXTURE_2D),
	m_atlasMipPaths(atlasMipPaths) {
	load();
}

AtlasTexture::~AtlasTexture() {
}

void AtlasTexture::load() {

	int width, height, nrChannels;
	unsigned char* data;

	unsigned int numMipMaps = m_atlasMipPaths.size();

	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, numMipMaps - 1);

	stbi_set_flip_vertically_on_load(true);

	for (int i = 0; i < numMipMaps; i++) {
		data = stbi_load(m_atlasMipPaths[i].c_str(), &width, &height, &nrChannels, 0);
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
				m_atlasWidth = width;
				m_atlasHeight = height;
			}
		}
		stbi_image_free(data);
	}
};