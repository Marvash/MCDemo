#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/CameraSystem/CameraRenderingData.h"
#include "Core/Services/Renderer/RendererStructs.h"


class Graphics : public CoreService {
public:

	Graphics(CoreEventDispatcher* coreEventDispatcher);
	void init(Renderer* renderer);
	void onNotify(Event& newEvent) override;
	void registerComponent(RenderingComponent* renderingComponent);
	void submitGUIElement(GUIElement* element);
	void setCameraRenderingData(CameraRenderingData* camera);
	float getViewportWidth();
	float getViewportHeight();

private:
	Renderer* m_renderer;
};