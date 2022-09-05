#include "IconLibrary.h"
#include <iostream>
#include <fstream>

IconLibrary::IconLibrary(Renderer* renderer, BiomeLibrary* biomeLibrary, Atlas* atlas) :
	m_renderer(renderer),
	m_atlas(atlas),
	m_biomeLibrary(biomeLibrary) {
	m_cubeVerticesTexIndexes = new GLint[(2 * 6 * 6)];
	m_itemVerticesTexIndexes = new GLint[(2 * 6)];
	generateBlockIcons();
	generateItemIcons();
}

IconLibrary::~IconLibrary() {
	int cubesCount = (int)CubeId::UNGENERATED_BLOCK;
	for (int i = 0; i < cubesCount; i++) {
		if (Cube::canBeRendered((CubeId)i)) {
			ItemId itemId = Cube::getItemId((CubeId)i);
			delete m_itemIcons[itemId];
		}
	}
	delete m_cubeVerticesTexIndexes;
	delete m_itemVerticesTexIndexes;
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
			size_t vertexIndexesBaseIndex = 0;
			int texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::BACK);
			int colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BACK);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::FRONT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::FRONT);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::LEFT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::LEFT);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::RIGHT);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::RIGHT);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::BOTTOM);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::BOTTOM);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			texCoordsIndex = m_atlas->getCubeTexIndex(cubeId, Cube::FaceSide::TOP);
			colorsIndex = m_biomeLibrary->getBiomeCubeColors(Biome::BiomeId::FOREST, cubeId, Cube::FaceSide::TOP);
			addFaceTexIndexes(m_cubeVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
			size_t vertexesCoordinatesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)3;
			size_t vertexesTexIndexesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)2;
			glBindVertexArray(renderData.modelData.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, m_iconCubeVertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, VBOTexIndices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, m_cubeVerticesTexIndexes, GL_STATIC_DRAW);
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

void IconLibrary::generateItemIcons() {
	generateItemIcon(ItemId::STICK);
	generateItemIcon(ItemId::WOODEN_AXE);
	generateItemIcon(ItemId::WOODEN_HOE);
	generateItemIcon(ItemId::WOODEN_PICKAXE);
	generateItemIcon(ItemId::WOODEN_SHOVEL);
	generateItemIcon(ItemId::WOODEN_SWORD);
	generateItemIcon(ItemId::STONE_AXE);
	generateItemIcon(ItemId::STONE_HOE);
	generateItemIcon(ItemId::STONE_PICKAXE);
	generateItemIcon(ItemId::STONE_SHOVEL);
	generateItemIcon(ItemId::STONE_SWORD);
}

void IconLibrary::generateItemIcon(ItemId itemId) {
	BOOST_LOG_TRIVIAL(info) << "Generating item icons...";
	OffScreenRenderData renderData;
	renderData.cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
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
	renderData.modelData.vertexCount = 6;
	renderData.modelData.position = glm::vec3(0.0f, 0.0f, 0.0f);
	renderData.projectionType = ProjectionType::ORTHOGRAPHIC;
	OrthographicData orthographicData;
	orthographicData.near = 0.01f;
	orthographicData.far = 2.0f;
	float halfIconSize = iconSize / 2.0f;
	orthographicData.l = -0.5f;
	orthographicData.r = 0.5f;
	orthographicData.b = -0.5f;
	orthographicData.t = 0.5f;
	renderData.projectionData = &orthographicData;
	unsigned char* result;
	BOOST_LOG_TRIVIAL(info) << "Generating icon " << (int)itemId;
	size_t vertexIndexesBaseIndex = 0;
	int texCoordsIndex = m_atlas->getItemTexIndex(itemId);
	int colorsIndex = 0;
	addFaceTexIndexes(m_itemVerticesTexIndexes, vertexIndexesBaseIndex, texCoordsIndex, colorsIndex);
	size_t vertexesCoordinatesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)3;
	size_t vertexesTexIndexesDataSize = (size_t)renderData.modelData.vertexCount * (size_t)2;
	glBindVertexArray(renderData.modelData.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexesCoordinatesDataSize, m_iconItemVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexIndices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * vertexesTexIndexesDataSize, m_itemVerticesTexIndexes, GL_STATIC_DRAW);
	glBindVertexArray(0);
	result = m_renderer->drawOffScreen(&renderData);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		BOOST_LOG_TRIVIAL(info) << "ERROR " << err;
	}

	m_itemIcons.insert(std::make_pair(itemId, new ImageTexture2D(renderData.renderingWidth, renderData.renderingHeight, GL_RGBA, GL_RGBA, result)));
	delete[] result;
	BOOST_LOG_TRIVIAL(info) << "Generated icon " << (int)itemId;
}

void IconLibrary::addFaceTexIndexes(GLint* buffer, size_t& vertexIndexesBaseIndex, int textureCoordinatesIndex, int colorIndex) {
	buffer[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	buffer[vertexIndexesBaseIndex++] = (GLint)textureCoordinatesIndex;
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	buffer[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 18);
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	buffer[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex);
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	buffer[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 12);
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;

	buffer[vertexIndexesBaseIndex++] = (GLint)(textureCoordinatesIndex + 6);
	buffer[vertexIndexesBaseIndex++] = (GLint)colorIndex;
}