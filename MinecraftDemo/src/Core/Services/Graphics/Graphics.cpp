#include "Graphics.h"

Graphics::Graphics(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_renderer(nullptr) {

}

void Graphics::init(Renderer* renderer) {
	m_renderer = renderer;
}

void Graphics::submitRenderableChunks(std::vector<ChunkRenderData*>* renderableChunks) {
	for (ChunkRenderData*& chunkRenderData : *renderableChunks) {
		m_renderer->submitChunk(*chunkRenderData);
	}
}

void Graphics::submitGUIElement(GUIElement* element) {
	m_renderer->submitGUIElement(element);
}

void Graphics::setCameraRenderingData(CameraRenderingData* cameraRenderingData) {
	m_renderer->setCameraRenderingData(cameraRenderingData);
}

void Graphics::onNotify(Event& newEvent) {

}