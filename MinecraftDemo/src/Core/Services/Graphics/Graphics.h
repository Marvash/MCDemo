#pragma once
#include "Core/Services/CoreService.h"
#include "Core/Services/Renderer/Renderer.h"
#include "Core/Chunk/Chunk.h"
#include "Core/Services/CameraSystem/CameraRenderingData.h"

class Graphics : public CoreService {
public:
	Graphics(CoreEventDispatcher* coreEventDispatcher);
	void init(Renderer* renderer);
	void onNotify(Event& newEvent) override;
	void submitRenderableChunks(std::vector<ChunkRenderData*>* renderableChunks);
	void submitGUIElement(GUIElement* element);
	void setCameraRenderingData(CameraRenderingData* camera);

private:
	Renderer* m_renderer;
};