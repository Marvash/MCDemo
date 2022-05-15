#pragma once
#include "Core/Layers/Layer.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/GUI/DebugGUI/DebugPanel.h"
#include "Core/Events/Game/PlayerMoveEvent.h"
#include "Core/Events/Game/PlayerLookEvent.h"
#include "Core/Events/Game/PlayerVelocityEvent.h"
#include "Core/Events/Game/PlayerSelectedCubeChange.h"

class GUILayer : public Layer {
public:
	GUILayer(CoreServiceLocator* coreServiceLocator);
	void onAdd() override;
	void onRemove() override;
	void update() override;
	void onNotify(Event& newEvent) override;

private:
	void updateDebugPanel();

	CoreServiceLocator* m_coreServiceLocator;
	DebugPanel* m_debugPanel;
};