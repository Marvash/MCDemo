#include "Chunk.h"
#include "Core/Services/CoreServiceLocator.h"

const float Chunk::blockSideSize = 1.0f;

Chunk::Chunk(BiomeManager* biomeManager, Atlas* atlas, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
	leftNeighbour(nullptr),
	rightNeighbour(nullptr),
	frontNeighbour(nullptr),
	backNeighbour(nullptr),
	chunkHeight(chunkHeight),
	chunkSideSize(chunkSideSize),
	chunkPosition(chunkPosition),
	init(false),
	state(ChunkState::SHOULDREGENERATE),
	canDraw(false),
	renderData({ 0, 0, glm::vec3(0.0f, 0.0f, 0.0f) }),
	m_atlas(atlas),
	m_biomeManager(biomeManager) {

	initEmptyBlockMatrix();
	renderingSetup();
}

Chunk::Chunk(BiomeManager* biomeManager, Atlas* atlas, Cube*** blockMatrix, int chunkHeight, int chunkSideSize, glm::vec3 chunkPosition) :
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
	canDraw(false),
	m_blockMatrix(blockMatrix),
	renderData({ 0, 0, glm::vec3(0.0f, 0.0f, 0.0f) }),
	m_atlas(atlas),
	m_biomeManager(biomeManager) {

	renderingSetup();
}

ChunkRenderData& Chunk::getChunkRenderData() {
	//BOOST_LOG_TRIVIAL(info) << "Pos: " << renderData.position.x << renderData.position.y << renderData.position.z << " count: " << renderData.indexCount;
	return renderData;
}

void Chunk::initEmptyBlockMatrix() {
	Cube*** m_blockMatrix = new Cube * *[chunkHeight];
	for (int i = 0; i < chunkHeight; i++) {
		m_blockMatrix[i] = new Cube * [chunkSideSize];
		for (int j = 0; j < chunkSideSize; j++) {
			m_blockMatrix[i][j] = new Cube[chunkSideSize];
			for (int k = 0; k < chunkSideSize; k++) {
				m_blockMatrix[i][j][k] = Cube(Cube::CubeId::UNGENERATED_BLOCK, this, nullptr);
			}
		}
	}
	this->m_blockMatrix = m_blockMatrix;
}

Cube*** Chunk::getBlockMatrix() {
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVTexIndexes);
	glVertexAttribIPointer(1, 1, GL_INT, 2 * sizeof(GLint), (void*)0);
	glVertexAttribIPointer(2, 1, GL_INT, 2 * sizeof(GLint), (void*)(sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	renderData.VAO = VAO;
	init = true;
}

void Chunk::loadMesh() {
	meshVertexesCount = newMeshVertexesCount;
	size_t vertexesCoordinatesDataSize = (size_t)meshVertexesCount * (size_t)3;
	size_t vertexesTexIndexesDataSize = (size_t)meshVertexesCount * (size_t)2;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, vertexesCoordinatesCompact, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVTexIndexes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, vertexesTexIndexesCompact, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	meshIndexesCount = newMeshIndexesCount;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (meshIndexesCount), indexesCompact, GL_STATIC_DRAW);
	glBindVertexArray(0);
	renderData.indexCount = meshIndexesCount;
	renderData.position = chunkPosition;
	cleanVerticesArrays();
}

void Chunk::addFaceCoordinates(size_t& vertexCoordsBaseIndex, Cube::FaceSide faceSide, float vertexBaseHeight, float vertexBaseWidth, float vertexBaseDepth) {
	float halfBlockSideSize = blockSideSize / 2.0f;
	switch (faceSide) {
	case Cube::FaceSide::TOP:
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
	case Cube::FaceSide::BOTTOM:
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
	case Cube::FaceSide::RIGHT:
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
	case Cube::FaceSide::LEFT:
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
	case Cube::FaceSide::FRONT:
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
	case Cube::FaceSide::BACK:
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

void Chunk::addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex) {
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)textureCoordinatesIndex;
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 6);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 18);
	vertexesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
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
	size_t verticesDataIndexesMaxSize = (size_t)chunkHeight * (size_t)chunkSideSize * (size_t)chunkSideSize * (size_t)(2 * 4 * 6);
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
				if (m_blockMatrix[i][j][w].getCubeId() == Cube::CubeId::AIR_BLOCK || m_blockMatrix[i][j][w].getCubeId() == Cube::CubeId::UNGENERATED_BLOCK) {
					continue;
				}
				float vertexBaseHeight = i + (blockSideSize / 2.0f);
				float vertexBaseWidth = j - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				float vertexBaseDepth = w - ((chunkSideSize / 2.0f) - (blockSideSize / 2.0f));
				size_t vertexCoordsBaseIndex = correctVertexCount * 3;
				size_t texCoordsBaseIndex = correctVertexCount * 2;
				int texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::TOP);
				int colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::TOP);
				//BOOST_LOG_TRIVIAL(info) << "tex: " << texCoordsIndex << "color: " << colorsIndex;
				// TOP
				Cube* neighbourCube = findNeighbourBlock(Cube::FaceSide::TOP, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {
					
					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::TOP, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 2;
				texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::BOTTOM);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::BOTTOM);
				// BOTTOM
				neighbourCube = findNeighbourBlock(Cube::FaceSide::BOTTOM, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {

					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::BOTTOM, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 2;
				texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::RIGHT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::RIGHT);
				// RIGHT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::RIGHT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {

					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::RIGHT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 2;
				texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::LEFT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::LEFT);
				// LEFT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::LEFT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {

					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::LEFT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 2;
				texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::FRONT);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::FRONT);
				// FRONT
				neighbourCube = findNeighbourBlock(Cube::FaceSide::FRONT, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {

					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::FRONT, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
					addFaceIndexes(vertexIndexBase, correctIndexCount);

					correctVertexCount += 4;
					vertexIndexBase += 4;

				}
				vertexCoordsBaseIndex = correctVertexCount * 3;
				texCoordsBaseIndex = correctVertexCount * 2;
				texCoordsIndex = m_atlas->getAtlasTexIndex(m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::BACK);
				colorsIndex = m_biomeManager->getBiomeCubeColors(m_blockMatrix[i][j][w].getBiomeRef()->m_biomeId, m_blockMatrix[i][j][w].getCubeId(), Cube::FaceSide::BACK);
				// BACK
				neighbourCube = findNeighbourBlock(Cube::FaceSide::BACK, i, j, w);
				if (neighbourCube != nullptr && neighbourCube->isTransparent()) {

					addFaceCoordinates(vertexCoordsBaseIndex, Cube::FaceSide::BACK, vertexBaseHeight, vertexBaseWidth, vertexBaseDepth);
					addFaceTexIndexes(texCoordsBaseIndex, texCoordsIndex, colorsIndex);
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
		size_t vertexIndexesDataSize = (size_t)newMeshVertexesCount * (size_t)2;
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

Cube* Chunk::getCubeByCoords(glm::vec3 coords) {
	glm::vec3 originChunkPos = chunkPosition;
	originChunkPos.x = originChunkPos.x - (chunkSideSize / 2.0f);
	originChunkPos.z = originChunkPos.z - (chunkSideSize / 2.0f);
	if (glm::abs(coords.x - originChunkPos.x) > chunkSideSize || glm::abs(coords.z - originChunkPos.z) > chunkSideSize || coords.y < originChunkPos.y || coords.y >= (chunkHeight + originChunkPos.y) /* || state < ChunkState::SHOULDREBUILD*/) {
		//BOOST_LOG_TRIVIAL(info) << coords.x << " " << coords.y << " " << coords.z;

		return nullptr;
	}
	int cubeWidthIndex = glm::abs(glm::floor((coords.x - originChunkPos.x)));
	int cubeDepthIndex = glm::abs(glm::floor((coords.z - originChunkPos.z)));
	int cubeHeightIndex = glm::abs(glm::floor((coords.y - originChunkPos.y)));
	return &m_blockMatrix[cubeHeightIndex][cubeWidthIndex][cubeDepthIndex];
}

Cube* Chunk::getBlockValue(int height, int width, int depth) {
	return &m_blockMatrix[height][width][depth];
}

Cube* Chunk::findNeighbourBlock(Cube::FaceSide neighbourSide, int height, int width, int depth) {
	Chunk* neighbourChunk = nullptr;
	Cube* neighbourCube = nullptr;
	switch (neighbourSide) {
	case Cube::FaceSide::LEFT:
		if (width == 0) {
			neighbourChunk = leftNeighbour;
			width = chunkSideSize - 1;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width -= 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::RIGHT:
		if (width == (chunkSideSize - 1)) {
			neighbourChunk = rightNeighbour;
			width = 0;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			width += 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::FRONT:
		if (depth == (chunkSideSize - 1)) {
			neighbourChunk = frontNeighbour;
			depth = 0;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth += 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::BACK:
		if (depth == 0) {
			neighbourChunk = backNeighbour;
			depth = chunkSideSize - 1;
			if (neighbourChunk != nullptr && neighbourChunk->state != ChunkState::ISREGENERATING && neighbourChunk->state != ChunkState::SHOULDREGENERATE) {
				neighbourCube = neighbourChunk->getBlockValue(height, width, depth);
			}
		}
		else {
			depth -= 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::TOP:
		if (height != (chunkHeight - 1)) {
			height += 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	case Cube::FaceSide::BOTTOM:
		if (height != 0) {
			height -= 1;
			neighbourCube = &m_blockMatrix[height][width][depth];
		}
		break;
	}
	return neighbourCube;
}

Cube* Chunk::findNeighbourBlock(Cube::FaceSide neighbourSide, Cube* cube) {
	int height, width, depth;
	for (height = 0; height < chunkHeight; height++) {
		for (width = 0; width < chunkSideSize; width++) {
			for (depth = 0; depth < chunkSideSize; depth++) {
				if (&m_blockMatrix[height][width][depth] == cube) {
					return findNeighbourBlock(neighbourSide, height, width, depth);
				}
			}
		}
	}
	return nullptr;
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

void Chunk::deleteChunkData(Cube*** chunkData, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete[] chunkData[i][j];
		}
		delete[] chunkData[i];
	}
	delete[] chunkData;
}