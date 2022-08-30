#include "IconLibrary.h"
#include <iostream>
#include <fstream>

IconLibrary::IconLibrary(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas) :
	m_renderer(renderer),
	m_atlas(atlas),
	m_biomeLibrary(biomeLibrary) {
	m_verticesTexIndexes = new GLint[(2 * 6 * 6)];
	generateBlockIcons();
}

IconLibrary::~IconLibrary() {
	int cubesCount = (int)CubeId::UNGENERATED_BLOCK;
	for (int i = 0; i < cubesCount; i++) {
		if (Cube::canBeRendered((CubeId)i)) {
			ItemId itemId = Cube::getItemId((CubeId)i);
			delete m_itemIcons[itemId];
		}
	}
	delete m_verticesTexIndexes;
}

ImageTexture2D* IconLibrary::getItemIcon(ItemId itemId) {
	return m_itemIcons[itemId];
}

void IconLibrary::generateBlockIcons() {
	BOOST_LOG_TRIVIAL(info) << "Generating block icons...";
	OffScreenRenderData renderData;
	int cubesCount = (int)CubeId::UNGENERATED_BLOCK;
	renderData.cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
	renderData.cameraDir = -renderData.cameraPos;
	renderData.clearColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	float viewportHeight = m_renderer->getViewportHeight();
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
		CubeId cubeId = (CubeId)i;
		BOOST_LOG_TRIVIAL(info) << "Generating icon " << Cube::getDisplayName(cubeId);
		if (Cube::canBeRendered(cubeId)) {
			int numFaces = 6;
			int positionOffset = 3;
			int strideSize = 5;
			int index = positionOffset;
			size_t vertexIndexesBaseIndex = 0;
			int texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::BACK);
			int colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BACK);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::FRONT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::FRONT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::LEFT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::LEFT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::RIGHT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::RIGHT);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::BOTTOM);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BOTTOM);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getAtlasTexIndex(cubeId, Cube::FaceSide::TOP);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::TOP);
			addFaceTexIndexes(vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			size_t vertexesCoordinatesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)3;
			size_t vertexesTexIndexesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)2;
			glBindVertexArray(renderData.modelData.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, m_iconCubeVertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, VBOTexIndices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, m_verticesTexIndexes, GL_STATIC_DRAW);
			glBindVertexArray(0);
			result = m_renderer->drawOffScreen(&renderData);
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR)
			{
				BOOST_LOG_TRIVIAL(info) << "ERROR " << err;
			}
			ItemId itemId = Cube::getItemId(cubeId);
			m_itemIcons.insert(std::make_pair(itemId, new ImageTexture2D(renderData.renderingWidth, renderData.renderingHeight, GL_RGBA, GL_RGBA, result)));
			delete[] result;
		}
	}
	BOOST_LOG_TRIVIAL(info) << "Generated " << m_itemIcons.size() << " block icons";
}

void IconLibrary::addFaceTexIndexes(size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex) {
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