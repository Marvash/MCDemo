#include "CoreEventDispatcher.h"

CoreEventDispatcher::CoreEventDispatcher() : m_subscribedServices(nullptr) {
	m_subscribedServices = new CoreService * [MAX_SUBS];
	for (int i = 0; i < MAX_SUBS; i++) {
		m_subscribedServices[i] = nullptr;
	}
}

CoreEventDispatcher::~CoreEventDispatcher() {
	delete[] m_subscribedServices;
}

void CoreEventDispatcher::addSubService(CoreService* coreService) {
	if (m_numSubs < MAX_SUBS) {
		m_subscribedServices[m_numSubs] = coreService;
		m_numSubs++;
	}
	else {
		// throw custom exception
		throw Exception("Max subscribers reached in core dispatcher");
	}
}

void CoreEventDispatcher::removeSubService(CoreService* coreService) {
	for (int i = 0; i < m_numSubs; i++) {
		if (m_subscribedServices[i] == coreService) {
			m_subscribedServices[i] = m_subscribedServices[m_numSubs - 1];
			m_subscribedServices[m_numSubs - 1] = nullptr;
			m_numSubs--;
		}
	}
}

void CoreEventDispatcher::setLayerStack(LayerStack* layerStack) {
	m_layerStack = layerStack;
}

void CoreEventDispatcher::notify(Event& event) {
	//BOOST_LOG_TRIVIAL(trace) << "Dispatching event: " << (int)event.getEventType();
	for (int i = 0; i < m_numSubs; i++)
	{
		m_subscribedServices[i]->onNotify(event);
		if (event.isHandled())
			return;
	}
	if (m_layerStack != nullptr) {
		m_layerStack->onNotify(event);
	}
}