#pragma once
#include "Core/Textures/AtlasTexture.h"
#include "Core/Textures/ImageTexture2D.h"
#include "Core/Textures/TextureBuffer.h"
#include "Core/Services/BlockLibrary/BlockIdEnum.h"
#include "Core/Services/BlockLibrary/BlockFaceEnum.h"
#include "Core/Services/ItemLibrary/ItemIdEnum.h"
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

	int getCubeTexIndex(BlockId blockId, BlockFace blockFace);
	int getItemTexIndex(ItemId itemId);

	TextureBuffer* getTexCoordsBuffer();
	AtlasTexture* getAtlasTexture();

	void init();
	void onNotify(Event& newEvent) override;
	void notify(Event& newEvent) override;

private:
	AtlasTexCoordinates* m_atlasTexCoords;
	AtlasTexture* m_texture;
	TextureBuffer* m_texCoords;
};