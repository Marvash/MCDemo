#pragma once
#include "Core/Events/Event.h"
#include "Core/LayerStack.h"
#include "Core/Services/CoreService.h"
#include "Core/Exceptions/Exception.h"
#include <Boost/log/trivial.hpp>

class CoreEventDispatcher
{
public:
	CoreEventDispatcher();
	~CoreEventDispatcher();
	void addSubService(CoreService* coreService);
	void removeSubService(CoreService* coreService);
	void setLayerStack(LayerStack* layerStack);
	void notify(Event& event);
private:
	const unsigned int MAX_SUBS = 1000;
	CoreService** m_subscribedServices;
	LayerStack* m_layerStack;
	int m_numSubs;
};

