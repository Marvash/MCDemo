#pragma once
#include "Core/Textures/AtlasTexture.h"
#include "Core/Textures/TextureBuffer.h"
#include "Core/Game/Cube/Cube.h"
#include "AtlasTexCoordinates.h"
#include <vector>
#include <string>
#include <Boost/log/trivial.hpp>

class Atlas
{
public:
	Atlas();
	~Atlas();

	int getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide);
	AtlasTexture* getAtlasTexture();
	TextureBuffer* getTexCoordsBuffer();

private:
	void init();

	AtlasTexCoordinates* m_atlasTexCoords;
	AtlasTexture* m_texture;
	TextureBuffer* m_texCoords;
};