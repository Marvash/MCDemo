#pragma once
#include "Core/Events/Event.h"
#include <Boost/log/trivial.hpp>

class CoreEventDispatcher;

class CoreService {
public:
	CoreService(CoreEventDispatcher* eventDispatcher = nullptr);
	virtual void onNotify(Event& newEvent) = 0;
	virtual void notify(Event& newEvent);
protected:
	CoreEventDispatcher* m_eventDispatcher;
};