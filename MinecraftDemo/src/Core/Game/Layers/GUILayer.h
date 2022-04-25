#pragma once
#include "Core/Layer/Layer.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Game/GUI/DebugGUI/DebugPanel.h"

class GUILayer : public Layer {
public:
	GUILayer(CoreServiceLocator* coreServiceLocator);
	void onAdd() override;
	void onRemove() override;
	void update() override;
	void onNotify(Event& newEvent) override;

private:
	CoreServiceLocator* m_coreServiceLocator;
	DebugPanel* m_debugPanel;
};