#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Events/Game/PlayerMoveEvent.h"

class World : public CoreService {
public:
	World(CoreEventDispatcher* coreEventDispatcher);
	void init(ChunkManager* chunkManager);
	void onNotify(Event& newEvent) override;
	void startThreads();
	void stopThreads();
	void reloadChunks();
	void updateRenderableChunks();
	std::vector<ChunkRenderData*>* getRenderableChunks();
	void destroyBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection);
	void placeBlock(glm::vec3 rayOrigin, glm::vec3& playerLookDirection, Cube::CubeId cubeId);

private:

	bool m_threadsRunning;
	ChunkManager* m_chunkManager;
};