#include "IconManager.h"

IconManager::IconManager(CoreServiceLocator* coreServiceLocator) :
	m_coreServiceLocator(coreServiceLocator) {
	m_verticesTexIndexes = new GLint[(2 * 6 * 6)];
	generateIcons();
}

IconManager::~IconManager() {
	int cubesCount = (int)Cube::CubeId::UNGENERATED_BLOCK;
	for (int i = 0; i < cubesCount; i++) {
		Cube::CubeId cubeId = (Cube::CubeId)i;
		delete m_cubeIcons[cubeId];
	}
	delete m_verticesTexIndexes;
}

ImageTexture2D* IconManager::getIcon(Cube::CubeId cubeId) {
	return m_cubeIcons[cubeId];
}

void IconManager::generateIcons() {
	BOOST_LOG_TRIVIAL(info) << "Generating block icons...";
	Graphics* graphics = m_coreServiceLocator->getGraphics();
	AtlasService* altas = m_coreServiceLocator->getAtlasService();
	BiomeService* biomeService = m_coreServiceLocator->getBiomeService();
	OffScreenRenderData renderData;
	int cubesCount = (int)Cube::CubeId::UNGENERATED_BLOCK;
	renderData.cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
	renderData.cameraDir = -renderData.cameraPos;
	renderData.clearColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	float viewportHeight = graphics->getViewportHeight();
	float iconSize = glm::round(viewportHeight / 10.0f);
	BOOST_LOG_TRIVIAL(info) << "Viewport height " << viewportHeight << " icon size " << iconSize;
	renderData.renderingHeight = iconSize;
	renderData.renderingWidth = iconSize;
	renderData.shaderType = ShaderType::WORLD;
	renderData.shaderData = nullptr;

	GLuint VBOvertices;
	GLuint VBOTexIndices;
	glGenVertexArrays(1, &renderData.modelData.VAO);
	glGenBuffers(1, &VBOvertices);
	glGenBuffers(1, &VBOTexIndices);
	glBindVertexArray(renderData.modelData.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexIndices);
	glVertexAttribIPointer(1, 1, GL_INT, 2 * sizeof(GLint), (void*)0);
	glVertexAttribIPointer(2, 1, GL_INT, 2 * sizeof(GLint), (void*)(sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	renderData.modelData.isIndexed = false;
	renderData.modelData.vertexCount = 36;
	renderData.modelData.position = glm::vec3(0.0f, 0.0f, 0.0f);
	renderData.projectionType = ProjectionType::ORTHOGRAPHIC;
	OrthographicData orthographicData;
	orthographicData.near = 0.01f;
	orthographicData.far = 2.0f;
	orthographicData.l = -0.83f;
	orthographicData.r = 0.83f;
	orthographicData.b = -0.83f;
	orthographicData.t = 0.83f;
	renderData.projectionData = &orthographicData;
	unsigned char* result;
	for (int i = 0; i < cubesCount; i++) {
		Cube::CubeId cubeId = (Cube::CubeId)i;
		BOOST_LOG_TRIVIAL(info) << "Generating icon " << Cube::getDisplayName(cubeId);
		if (Cube::canBeRendered(cubeId)) {
			int numFaces = 6;
			int positionOffset = 3;
			int strideSize = 5;
			int index = positionOffset;
			size_t vertexIndexesBaseIndex = 0;
			int texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::BACK);
			int colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BACK);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::FRONT);
			colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::FRONT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::LEFT);
			colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::LEFT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::RIGHT);
			colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::RIGHT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::BOTTOM);
			colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BOTTOM);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = altas->getAtlasTexIndex(cubeId, Cube::FaceSide::TOP);
			colorsIndex = biomeService->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::TOP);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			size_t vertexesCoordinatesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)3;
			size_t vertexesTexIndexesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)2;
			glBindVertexArray(renderData.modelData.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, m_iconCubeVertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, VBOTexIndices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, m_verticesTexIndexes, GL_STATIC_DRAW);
			glBindVertexArray(0);
			result = graphics->drawOffScreen(&renderData);
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR)
			{
				BOOST_LOG_TRIVIAL(info) << "ERROR " << err;
			}
			m_cubeIcons.insert(std::make_pair(cubeId, new ImageTexture2D(renderData.renderingWidth, renderData.renderingHeight, GL_RGBA, GL_RGBA, result)));
			delete[] result;
		}
	}
	BOOST_LOG_TRIVIAL(info) << "Generated " << m_cubeIcons.size() << " block icons";
}

void IconManager::addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex) {
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)textureCoordinatesIndex;
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 18);
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex);
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 6);
	m_verticesTexIndexes[vertexIndexesBaseIndex++] = (GLint)colorIndex;
}