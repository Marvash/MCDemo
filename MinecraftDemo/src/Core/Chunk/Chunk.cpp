#include "Chunk.h"
#include "Core/Services/BlockLibrary/BlockManager.h"

const float Chunk::blockSideSize = 1.0f;

Chunk::Chunk(BlockManager* blockManager, BiomeLibrary* biomeManager, Atlas* atlas, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight),
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	init(false),
	state(ChunkState::SHOULDREGENERATE),
	m_atlas(atlas),
	m_biomeManager(biomeManager),
	m_blockManager(blockManager) {

	initEmptyBlockMatrix();
	renderingSetup();
}

Chunk::Chunk(BlockManager* blockManager, BiomeLibrary* biomeManager, Atlas* atlas, Block*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight), 
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	vertexesCoordinates(nullptr),
	vertexesCoordinatesCompact(nullptr),
	indexes(nullptr),
	indexesCompact(nullptr),
	vertexesTexIndexes(nullptr),
	vertexesTexIndexesCompact(nullptr),
	init(false),
	state(ChunkState::SHOULDREGENERATE),
	m_blockMatrix(blockMatrix),
	m_atlas(atlas),
	m_biomeManager(biomeManager),
	m_blockManager(blockManager) {

	renderingSetup();
}

RenderingComponent* Chunk::getRenderingComponent() {
	//BOOST_LOG_TRIVIAL(info) << "Pos: " << renderData.position.x << renderData.position.y << renderData.position.z << " count: " << renderData.indexCount;
	return &m_renderingComponent;
}

void Chunk::initEmptyBlockMatrix() {
	//BOOST_LOG_TRIVIAL(info) << "Chunk pos x: " << chunkPosition.x << " y: " << chunkPosition.y << " z: " << chunkPosition.z;
	float halfBlockSideSize = blockSideSize / 2.0f;
	Block*** m_blockMatrix = new Block * *[chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		m_blockMatrix[i] = new Block * [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			m_blockMatrix[i][j] = new Block[chunkSideSize];
			for (int k = 0; k < chunkSideSize; k++) {
				float xOffset = (j + halfBlockSideSize);
				float yOffset = (i + halfBlockSideSize);
				float zOffset = (k + halfBlockSideSize);
				glm::vec3 offset((j + halfBlockSideSize), (i + halfBlockSideSize), (k + halfBlockSideSize));
				m_blockMatrix[i][j][k] = Block(BlockId::NONE, this, offset);
			}
		}
	}
	this->m_blockMatrix = m_blockMatrix;
}

Block*** Chunk::getBlockMatrix() {
	return m_blockMatrix;
}

void Chunk::setPosition(glm::vec3& position) {
	chunkPosition = position;
}

void Chunk::renderingSetup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBOVCoords);
	glGenBuffers(1, &VBOVTexIndexes);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVCoords);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVTexIndexes);
	glVertexAttribIPointer(1, 1, GL_INT, 3 * sizeof(GLint), (void*)0);
	glVertexAttribIPointer(2, 1, GL_INT, 3 * sizeof(GLint), (void*)(sizeof(GLint)));
	glVertexAttribIPointer(3, 1, GL_INT, 3 * sizeof(GLint), (void*)(2*sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_renderingComponent.m_modelData.VAO = VAO;
	m_renderingComponent.m_modelData.isIndexed = true;
	m_renderingComponent.m_shaderType = ShaderType::WORLD;
	m_renderingComponent.m_shaderData = nullptr;
	init = true;
}

void Chunk::loadMesh() {
	meshVertexesCount = newMeshVertexesCount;
	size_t vertexesCoordinatesDataSize = (size_t)meshVertexesCount * (size_t)3;
	size_t vertexesTexIndexesDataSize = (size_t)meshVertexesCount * (size_t)3;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, vertexesCoordinatesCompact, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVTexIndexes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, vertexesTexIndexesCompact, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	meshIndexesCount = newMeshIndexesCount;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (meshIndexesCount), indexesCompact, GL_STATIC_DRAW);
	glBindVertexArray(0);
	m_renderingComponent.m_modelData.indexCount = meshIndexesCount;
	m_renderingComponent.m_modelData.position = chunkPosition;
	cleanVerticesArrays();
}

void Chunk::addFaceCoordinates(size_t& vertexCoordsBaseIndex, BlockFace faceSide, float vertexBaseHeight, float vertexBaseWidth, float vertexBaseDepth) {
	float halfBlockSideSize = blockSideSize / 2.0f;
	switch (faceSide) {
	case BlockFace::TOP:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);
		break;
	case BlockFace::BOTTOM:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);
		break;
	case BlockFace::RIGHT:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);
		break;
	case BlockFace::LEFT:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);
		break;
	case BlockFace::FRONT:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth + halfBlockSideSize);
		break;
	case BlockFace::BACK:
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);

		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseWidth + halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseHeight - halfBlockSideSize);
		vertexesCoordinates[vertexCoordsBaseIndex++] = (GLfloat)(vertexBaseDepth - halfBlockSideSize);
		break;
	}
}

void Chunk::addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex, int secondaryTextureCoordinatesIndex) {

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)textureCoordinatesIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)secondaryTextureCoordinatesIndex != -1 ? (GLint)secondaryTextureCoordinatesIndex : -1;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 6);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = secondaryTextureCoordinatesIndex != -1 ? (GLint)(secondaryTextureCoordinatesIndex + 2) : -1;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = secondaryTextureCoordinatesIndex != -1 ? (GLint)(secondaryTextureCoordinatesIndex + 4) : -1;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 18);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = secondaryTextureCoordinatesIndex != -1 ? (GLint)(secondaryTextureCoordinatesIndex + 6) : -1;
}

void Chunk::addFaceIndexes(GLuint vertexBaseIndex, size_t& indexCount) {
	indexes[indexCount++] = vertexBaseIndex;
	indexes[indexCount++] = vertexBaseIndex + 3;
	indexes[indexCount++] = vertexBaseIndex + 1;
	indexes[indexCount++] = vertexBaseIndex + 2;
	indexes[indexCount++] = vertexBaseIndex + 1;
	indexes[indexCount++] = vertexBaseIndex + 3;
}

void Chunk::buildMesh() {
	cleanVerticesArrays();
	size_t verticesCoordinatesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)(3 * 4 * 6);
	size_t verticesDataIndexesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)(3 * 4 * 6);
	size_t indicesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)36;
	vertexesCoordinates = new GLfloat[verticesCoordinatesMaxSize];
	vertexesTexIndexes = new GLint[verticesDataIndexesMaxSize];
	indexes = new GLuint[indicesMaxSize];
	size_t correctVertexCount = 0;
	size_t correctIndexCount = 0;
	GLuint vertexIndexBase = 0;
	for (int i = 0; i < chunkHeight; i++) {
		for (int j = 0; j < chunkSideSize; j++) {
			for (int w = 0; w < chunkSideSize; w++) {
				if (!m_blockManager->isRenderable(m_blockMatrix[i][j][w].getBlockId())) {
					continue;
				}
				/*
				float vertexBaseHeight = i + (blockSideSize / 2.0f);
				float vertexBaseWidth = j - ((chunkSideSize / 2.0f) + (blockSideSize / 2.0f));
				float vertexBaseDepth = w - ((chunkSideSize / 2.0f) + (blockSideSize / 2.0f));
				*/
				glm::vec3 cubeOffset = m_blockMatrix[i][j][w].getBlockCoordsOffset();
				float vertexBaseHeight = (cubeOffset.y);
				float vertexBaseWidth = (cubeOffset.x - (chunkSideSize / 2));
				float vertexBaseDepth = (cubeOffset.z - (chunkSideSize / 2));
				size_t vertexCoordsBaseIndex = correctVertexCount * 3;
				size_t texCoordsBaseIndex = correctVertexCount * 3;
				int texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::TOP);
				int colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::TOP);
				int secondaryTexCoordsIndex = m_blockManager->isBlockBeingBroken(&m_blockMatrix[i][j][w]) ? m_atlas->getBlockSecondaryTexIndex(m_blockManager->getBreakingStage()) : -1;
				//BOOST_LOG_TRIVIAL(info) << "tex: " << texCoordsIndex << "color: " << colorsIndex;
				// TOP
				Block* neighbourBlock = findNeighbourBlock(BlockFace::TOP, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {
					
					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::TOP, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 3;
				texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::BOTTOM);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::BOTTOM);
				// BOTTOM
				neighbourBlock = findNeighbourBlock(BlockFace::BOTTOM, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {

					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::BOTTOM, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 3;
				texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::RIGHT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::RIGHT);
				// RIGHT
				neighbourBlock = findNeighbourBlock(BlockFace::RIGHT, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {

					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::RIGHT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 3;
				texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::LEFT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::LEFT);
				// LEFT
				neighbourBlock = findNeighbourBlock(BlockFace::LEFT, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {

					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::LEFT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 3;
				texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::FRONT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::FRONT);
				// FRONT
				neighbourBlock = findNeighbourBlock(BlockFace::FRONT, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {

					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::FRONT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 3;
				texCoordsIndex = m_atlas->getBlockTexIndex(m_blockMatrix[i][j][w].getBlockId(), BlockFace::BACK);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getBlockId(), BlockFace::BACK);
				// BACK
				neighbourBlock = findNeighbourBlock(BlockFace::BACK, i, j, w);
				if (neighbourBlock != nullptr && m_blockManager->isTransparent(neighbourBlock->getBlockId())) {

					addFaceCoordinates(vertexCoordsBaseIndex, BlockFace::BACK, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex, secondaryTexCoordsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
			}
		}
	}

	if (correctIndexCount > 0 && correctVertexCount > 2) {
		newMeshIndexesCount = correctIndexCount;
		newMeshVertexesCount = correctVertexCount;
		size_t vertexCoordinatesDataSize = (size_t)newMeshVertexesCount * (size_t)3;
		size_t vertexIndexesDataSize = (size_t)newMeshVertexesCount * (size_t)3;
		vertexesCoordinatesCompact = new GLfloat[vertexCoordinatesDataSize];
		vertexesTexIndexesCompact = new GLint[vertexIndexesDataSize];
		indexesCompact = new GLuint[newMeshIndexesCount];
		for (size_t i = 0; i < vertexCoordinatesDataSize; i++) {
			vertexesCoordinatesCompact[i] = vertexesCoordinates[i];
		}

		for (size_t i = 0; i < vertexIndexesDataSize; i++) {
			vertexesTexIndexesCompact[i] = vertexesTexIndexes[i];
		}
		
		for (size_t i = 0; i < newMeshIndexesCount; i++) {
			indexesCompact[i] = indexes[i];
		}
	}
}

void Chunk::cleanVerticesArrays() {
	delete[] vertexesCoordinatesCompact;
	delete[] vertexesTexIndexesCompact;
	delete[] indexesCompact;
	vertexesCoordinatesCompact = nullptr;
	vertexesTexIndexesCompact = nullptr;
	indexesCompact = nullptr;
	delete[] vertexesCoordinates;
	delete[] vertexesTexIndexes;
	delete[] indexes;
	vertexesCoordinates = nullptr;
	vertexesTexIndexes = nullptr;
	indexes = nullptr;
}

Block* Chunk::getCubeByCoords(glm::f64vec3 coords) {
	glm::f64vec3 originChunkPos = chunkPosition;
	//BOOST_LOG_TRIVIAL(info) << "o: " << originChunkPos.x << " " << originChunkPos.y << " " << originChunkPos.z;
	//BOOST_LOG_TRIVIAL(info) << "c: " << coords.x << " " << coords.y << " " << coords.z;
	originChunkPos.x = originChunkPos.x - ((double)chunkSideSize / 2.0);
	originChunkPos.z = originChunkPos.z - ((double)chunkSideSize / 2.0);
	//BOOST_LOG_TRIVIAL(info) << "o2: " << originChunkPos.x << " " << originChunkPos.y << " " << originChunkPos.z;
	if (glm::abs(coords.x - originChunkPos.x) > (double)chunkSideSize || glm::abs(coords.z - originChunkPos.z) > (double)chunkSideSize || coords.y < originChunkPos.y || coords.y >= ((double)chunkHeight + originChunkPos.y) /* || state < ChunkState::SHOULDREBUILD*/) {
		//BOOST_LOG_TRIVIAL(info) << coords.x << " " << coords.y << " " << coords.z;

		return nullptr;
	}
	int cubeWidthIndex = glm::abs(glm::floor((coords.x - originChunkPos.x)));
	int cubeDepthIndex = glm::abs(glm::floor((coords.z - originChunkPos.z)));
	int cubeHeightIndex = glm::abs(glm::floor((coords.y - originChunkPos.y)));
	//BOOST_LOG_TRIVIAL(info) << "f: " << cubeWidthIndex << " " << cubeHeightIndex << " " << cubeDepthIndex;
	return &m_blockMatrix[cubeHeightIndex][cubeWidthIndex][cubeDepthIndex];
}

Block* Chunk::getBlockValue(int height, int width, int depth) {
	return &m_blockMatrix[height][width][depth];
}

Block* Chunk::findNeighbourBlock(BlockFace neighbourSide, int height, int width, int depth) {
	Chunk* neighbourChunk = nullptr;
	Block* neighbourBlock = nullptr;
	switch (neighbourSide) {
	case BlockFace::LEFT:
		if (width == 0) {
			neighbourChunk = leftNeighbour;
			width = chunkSideSize - 1;
			if (neighbourChunk != nullptr) {
				neighbourBlock = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width -= 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	case BlockFace::RIGHT:
		if (width == (chunkSideSize - 1)) {
			neighbourChunk = rightNeighbour;
			width = 0;
			if (neighbourChunk != nullptr) {
				neighbourBlock = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width += 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	case BlockFace::FRONT:
		if (depth == (chunkSideSize - 1)) {
			neighbourChunk = frontNeighbour;
			depth = 0;
			if (neighbourChunk != nullptr) {
				neighbourBlock = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth += 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	case BlockFace::BACK:
		if (depth == 0) {
			neighbourChunk = backNeighbour;
			depth = chunkSideSize - 1;
			if (neighbourChunk != nullptr) {
				neighbourBlock = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth -= 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	case BlockFace::TOP:
		if (height != (chunkHeight - 1)) {
			height += 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	case BlockFace::BOTTOM:
		if (height != 0) {
			height -= 1;
			neighbourBlock = &m_blockMatrix[height][width][depth];
		}
		break;
	}
	return neighbourBlock;
}

Block* Chunk::findNeighbourBlock(BlockFace neighbourSide, Block* block) {
	int height, width, depth;
	glm::vec3 blockOffset = block->getBlockCoordsOffset();
	width = int(blockOffset.x);
	height = int(blockOffset.y);
	depth = int(blockOffset.z);
	if (&m_blockMatrix[height][width][depth] == block) {
		return findNeighbourBlock(neighbourSide, height, width, depth);
	}
	return nullptr;
}

void Chunk::forceChunkMeshUpdate() {
	buildMesh();
	loadMesh();
	state = Chunk::ChunkState::MESHLOADED;
	if (leftNeighbour != nullptr) {
		leftNeighbour->buildMesh();
		leftNeighbour->loadMesh();
		leftNeighbour->state = Chunk::ChunkState::MESHLOADED;
	}
	if (rightNeighbour != nullptr) {
		rightNeighbour->buildMesh();
		rightNeighbour->loadMesh();
		rightNeighbour->state = Chunk::ChunkState::MESHLOADED;
	}
	if (frontNeighbour != nullptr) {
		frontNeighbour->buildMesh();
		frontNeighbour->loadMesh();
		frontNeighbour->state = Chunk::ChunkState::MESHLOADED;
	}
	if (backNeighbour != nullptr) {
		backNeighbour->buildMesh();
		backNeighbour->loadMesh();
		backNeighbour->state = Chunk::ChunkState::MESHLOADED;
	}
}

Chunk::~Chunk() {
	if (leftNeighbour != nullptr) {
		leftNeighbour->rightNeighbour = nullptr;
	}
	if (rightNeighbour != nullptr) {
		rightNeighbour->leftNeighbour = nullptr;
	}
	if (backNeighbour != nullptr) {
		backNeighbour->frontNeighbour = nullptr;
	}
	if (frontNeighbour != nullptr) {
		frontNeighbour->backNeighbour = nullptr;
	}
	glDeleteVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVCoords);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glDeleteBuffers(1, &VBOVCoords);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVTexIndexes);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glDeleteBuffers(1, &VBOVTexIndexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glDeleteBuffers(1, &EBO);
	deleteChunkData(m_blockMatrix, chunkHeight, chunkSideSize);
	cleanVerticesArrays();
}

void Chunk::deleteChunkData(Block*** chunkData, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete[] chunkData[i][j];
		}
		delete[] chunkData[i];
	}
	delete[] chunkData;
}