#include "Graphics.h"

Graphics::Graphics(CoreEventDispatcher* coreEventDispatcher) :
	CoreService(coreEventDispatcher),
	m_renderer(nullptr) {

}

void Graphics::init(Renderer* renderer) {
	m_renderer = renderer;
}

void Graphics::registerComponent(RenderingComponent* renderingComponent) {
	m_renderer->registerComponent(renderingComponent);
}

void Graphics::submitGUIElement(GUIElement* element) {
	m_renderer->submitGUIElement(element);
}

void Graphics::setCameraRenderingData(CameraRenderingData* cameraRenderingData) {
	m_renderer->setCameraRenderingData(cameraRenderingData);
}

float Graphics::getViewportWidth() {
	return m_renderer->getViewportWidth();
}

float Graphics::getViewportHeight() {
	return m_renderer->getViewportHeight();
}

unsigned char* Graphics::drawOffScreen(OffScreenRenderData* renderData) {
	return m_renderer->drawOffScreen(renderData);
}

void Graphics::onNotify(Event& newEvent) {

}