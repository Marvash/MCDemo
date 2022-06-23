#pragma once
#include "Core/Layers/Layer.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/GUI/DebugGUI/DebugPanel.h"
#include "Core/GUI/Crosshair.h"

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
	Crosshair* m_crosshair;
};