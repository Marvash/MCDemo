#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Services/CameraSystem/CameraRenderingData.h"
#include "Core/Services/Renderer/RendererStructs.h"
#include "Core/GUI/GUIElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
	unsigned char* drawOffScreen(OffScreenRenderData* renderData);

private:
	Renderer* m_renderer;
};