#pragma once
#include "Core/Services/CoreService.h"
#include "Core/States/CoreStateEnum.h"

class Core;

class ApplicationManager : public CoreService {

friend class Core;

public:
	ApplicationManager(Core* core, CoreEventDispatcher* eventDispatcher);

	void requestCoreStateChange(CoreState nextState);
	double getDeltaTime();
	void onNotify(Event& newEvent) override;

private:
	Core* m_core;
	double m_deltaTime;
};