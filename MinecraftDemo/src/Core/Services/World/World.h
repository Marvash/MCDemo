#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/ChunkManager/ChunkManager.h"
#include "Core/Components/RenderingComponent.h"
#include "Core/Services/CameraSystem/CameraSystem.h"

class World : public CoreService {
public:
	World(CoreEventDispatcher* coreEventDispatcher);
	void init(ChunkManager* chunkManager, CameraSystem* cameraSystem);
	void onNotify(Event& newEvent) override;
	void startThreads();
	void stopThreads();
	void reloadChunks();
	void updateGenerationOrigin(glm::vec3& position);
	std::vector<RenderingComponent*>* getChunkComponents();
	
	Block* getCubeByCoords(glm::vec3 coords);
	glm::vec3 getCubeAbsCoords(Block* cube);
	Block* getFirstNonEmptyBlock(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
	Block* getLastEmptyBlock(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
private:
	void getCubesInRay(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength, std::vector<Block*>& cubes);

	bool m_threadsRunning;
	ChunkManager* m_chunkManager;
	CameraSystem* m_cameraSystem;
};