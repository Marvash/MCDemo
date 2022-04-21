#pragma once
#include "Core/GameObject/GameObject.h"
#include "Chunk.h"
#include "Core/Game/Cube/Cube.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Game/RayCast/RayCast.h"
#include "Core/Game/TerrainGenerator/TerrainGenerator.h"
#include "Core/Game/GameServiceLocator/GameServiceLocator.h"
#include <Boost/log/trivial.hpp>



class ChunkManager {
public:
	static const int CHUNK_SIDE_SIZE;
	static const int CHUNK_HEIGHT;
	static const int SEA_LEVEL_OFFSET;
	boost::mutex m_internalLockLP;
	boost::mutex m_internalLockNext;
	boost::mutex m_internalLockData;
	int test = 0;
	TerrainGenerator m_terrainGen;

	ChunkManager(GameServiceLocator* gameServiceLocator, glm::vec3 origin);
	~ChunkManager();
	void generateChunks();
	void submitRenderableChunks(Renderer* renderer);
	void rebuildChunks();
	void reloadChunks();
	void startBuilderThreads();
	void startGeneratorThreads();
	void destroyBlock();
	void placeBlock(Cube::CubeId cubeId);
	void updateGenerationOrigin(glm::vec3& playerPos, glm::vec3& playerLookDir);
	Cube* getCubeByCoords(glm::vec3 coords);

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
	glm::vec3 m_playerLookDirection;
	GameServiceLocator* m_gameServiceLocator;
	
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