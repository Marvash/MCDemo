#include "CoreService.h"
#include "Core/CoreEventDispatcher.h"

CoreService::CoreService(CoreEventDispatcher* eventDispatcher) : m_eventDispatcher(eventDispatcher) {

}

void CoreService::notify(Event& newEvent) {
	BOOST_LOG_TRIVIAL(trace) << "Here disp";
	if (m_eventDispatcher != nullptr) {
		BOOST_LOG_TRIVIAL(trace) << "Calling dispatcher";
		m_eventDispatcher->notify(newEvent);
	}
}