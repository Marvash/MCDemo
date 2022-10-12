#include "CoreService.h"
#include "Core/CoreEventDispatcher.h"

CoreService::CoreService(CoreEventDispatcher* eventDispatcher) : m_eventDispatcher(eventDispatcher) {

}

void CoreService::notify(Event& newEvent) {
	if (m_eventDispatcher != nullptr) {
		m_eventDispatcher->notify(newEvent);
	}
}