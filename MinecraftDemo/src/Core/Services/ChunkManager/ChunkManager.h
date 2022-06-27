#pragma once
#include "Core/GameObject/GameObject.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Cube/Cube.h"
#include "Core/TerrainGenerator/TerrainGenerator.h"
#include "Core/Services/CoreService.h"
#include "Core/Services/Atlas/Atlas.h"
#include "Core/Services/BiomeManager/BiomeManager.h"
#include <Boost/log/trivial.hpp>

class CoreServiceLocator;

class ChunkManager : public CoreService {
public:
	static const int CHUNK_SIDE_SIZE;
	static const int CHUNK_HEIGHT;
	static const int SEA_LEVEL_OFFSET;
	boost::mutex m_internalLockLP;
	boost::mutex m_internalLockNext;
	boost::mutex m_internalLockData;
	int test = 0;
	TerrainGenerator* m_terrainGen;

	ChunkManager(CoreEventDispatcher* eventDispatcher);
	~ChunkManager();
	void generateChunks();
	void updateRenderableChunks();
	std::vector<ChunkRenderData*>* getRenderableChunks();
	void rebuildChunks();
	void reloadChunks();
	void startBuilderThreads();
	void startGeneratorThreads();
	void stopBuilderThreads();
	void stopGeneratorThreads();
	void destroyBlock(Cube* toDestroy);
	void placeBlock(Cube* toPlace, Cube::CubeId cubeId);
	void updateGenerationOrigin(glm::vec3& playerPos);
	Cube* getCubeByCoords(glm::f64vec3 coords);
	void convertToCenteredCubeCoordinates(glm::vec3& coords);
	void init(BiomeManager* biomeManager, Atlas* atlas);
	void computeAdjacentCubes(Cube*** adjacentCubes, GameObject* gameObject, int radius);
	void onNotify(Event& newEvent) override;
	void notify(Event& newEvent) override;
	Cube* solidBlockCast(glm::vec3& rayOrigin, glm::vec3& direction, float rayLength);
	glm::vec3 getCubeAbsCoords(Cube* cube);
	std::vector<Cube*> getCubesInRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength);
	void getCubesInRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, float rayLength, std::vector<Cube*>& cubes);

private:
	enum class ChunkSide {
		LEFT,
		RIGHT,
		BOTTOM,
		TOP
	};

	static const int CHUNK_ARRAY_WIDTH;
	static const int CHUNK_ARRAY_DEPTH;
	static const int N_WORKERS_REGEN;
	static const int N_WORKERS_REBUILD;

	Chunk*** m_chunkMatrix;
	glm::vec3 m_generationOrigin;
	glm::vec3 m_playerPosition;
	std::vector<ChunkRenderData*> m_renderableChunks;
	
	bool m_buildersShouldStop;
	bool m_generatorsShouldStop;
	boost::thread_group m_generatorThreads;
	boost::thread_group m_builderThreads;

	void generateSingleChunk(glm::vec3 chunkPosition, int widthIndex, int depthIndex, Chunk* chunk);
	void resetNeighbours();
	void moveChunkMatrix(ChunkSide side);
	void generatorThreadFunction();
	void builderThreadFunction();

	void lockHP();
	void unlockHP();
	void lockLP();
	void unlockLP();
};