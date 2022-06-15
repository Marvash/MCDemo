#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"

class World : public CoreService {
public:
	World(CoreEventDispatcher* coreEventDispatcher);
	void init(ChunkManager* chunkManager);
	void onNotify(Event& newEvent) override;
	void startThreads();
	void stopThreads();
	void reloadChunks();
	void updateRenderableChunks();
	void updateGenerationOrigin(glm::vec3& position);
	std::vector<ChunkRenderData*>* getRenderableChunks();
	void getCubesInRay(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength, std::vector<Cube*>& cubes);
	void destroyBlock(Cube* toDestroy);
	void placeBlock(Cube* toPlace, Cube::CubeId cubeId);

private:

	bool m_threadsRunning;
	ChunkManager* m_chunkManager;
};