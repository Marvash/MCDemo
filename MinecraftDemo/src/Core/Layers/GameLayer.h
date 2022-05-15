#pragma once
#include "Layer.h"
#include "Core/Player/Player.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Events/KeyEvent.h"

class GameLayer : public Layer {
public:
	GameLayer(CoreServiceLocator* coreServiceLocator);

	void onAdd() override;
	void onRemove() override;
	void update() override;
	void onNotify(Event& newEvent) override;

private:

	CoreServiceLocator* m_coreServiceLocator;
	Player* m_player;
};