#pragma once
#include "Core/Events/Event.h"

class CoreServiceLocator;

class GUIElement {
public:
	GUIElement(CoreServiceLocator* coreServiceLocator) : m_coreServiceLocator(coreServiceLocator) {};
	virtual void onNotify(Event& newEvent) {};
	virtual void draw() = 0;
protected:
	CoreServiceLocator* m_coreServiceLocator;
};