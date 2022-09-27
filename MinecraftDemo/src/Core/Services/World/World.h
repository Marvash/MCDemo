#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Components/RenderingComponent.h"

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
	std::vector<RenderingComponent*>* getChunkComponents();
	void getCubesInRay(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength, std::vector<Block*>& cubes);
	Block* getCubeByCoords(glm::vec3 coords);
	glm::vec3 getCubeAbsCoords(Block* cube);

private:

	bool m_threadsRunning;
	ChunkManager* m_chunkManager;
};