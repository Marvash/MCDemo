#pragma once
#include "Core/Layers/Layer.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/GUI/DebugGUI/DebugPanel.h"
#include "Core/GUI/Crosshair.h"
#include "Core/GUI/ItemBar.h"
#include "Core/GUI/InventoryGUI.h"

class GameGUILayer : public Layer {
public:
	GameGUILayer(CoreServiceLocator* coreServiceLocator);
	void onAdd() override;
	void onRemove() override;
	void update() override;
	void onNotify(Event& newEvent) override;

private:

	CoreServiceLocator* m_coreServiceLocator;
	DebugPanel* m_debugPanel;
	Crosshair* m_crosshair;
	ItemBar* m_itemBar;
	InventoryGUI* m_inventory;
};