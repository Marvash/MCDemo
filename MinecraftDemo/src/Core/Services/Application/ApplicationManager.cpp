#include "ApplicationManager.h"
#include "Core/Core.h"

ApplicationManager::ApplicationManager(Core* core, CoreEventDispatcher* eventDispatcher) : CoreService(eventDispatcher),
	m_core(core),
	m_deltaTime(0.0) {

}

void ApplicationManager::requestCoreStateChange(CoreState nextState) {
	m_core->setNextState(nextState);
}

void ApplicationManager::onNotify(Event& newEvent) {

}

double ApplicationManager::getDeltaTime() {
	return m_deltaTime;
}