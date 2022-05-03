#pragma once
#include "Core/Textures/AtlasTexture.h"
#include "Core/Textures/TextureBuffer.h"
#include "Core/Cube/Cube.h"
#include "Core/Atlas/AtlasTexCoordinates.h"
#include "Core/Services/CoreService.h"
#include "Core/CoreEventDispatcher.h"
#include <vector>
#include <string>
#include <Boost/log/trivial.hpp>

class Atlas : public CoreService
{
public:
	Atlas(CoreEventDispatcher* coreEventDispatcher);
	~Atlas();

	int getAtlasTexIndex(Cube::CubeId cubeId, Cube::FaceSide faceSide);
	AtlasTexture* getAtlasTexture();
	TextureBuffer* getTexCoordsBuffer();
	void init();
	void onNotify(Event& newEvent) override;
	void notify(Event& newEvent) override;

private:
	AtlasTexCoordinates* m_atlasTexCoords;
	AtlasTexture* m_texture;
	TextureBuffer* m_texCoords;
};