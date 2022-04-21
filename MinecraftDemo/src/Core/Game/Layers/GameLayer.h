#pragma once
#include "Core/Layer/Layer.h"
#include "Core/Game/Atlas/Atlas.h"
#include "Core/Game/Chunk/ChunkManager.h"
#include "Core/Game/Player/Player.h"
#include "Core/Game/Biomes/BiomeManager.h"
#include "Core/Game/GameServiceLocator/GameServiceLocator.h"
#include "Core/Events/KeyEvent.h"

class GameLayer : public Layer {
public:
	GameLayer(CoreServiceLocator* coreServiceLocator);

	void onAdd() override;
	void onRemove() override;
	void update() override;
	void onNotify(Event& newEvent) override;

private:
	void requestApplicationQuit();

	GameServiceLocator* m_gameServiceLocator;
	Atlas* m_atlas;
	ChunkManager* m_chunkManager;
	Player* m_player;
	BiomeManager* m_biomeManager;
	CoreServiceLocator* m_coreServiceLocator;
};