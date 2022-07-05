#pragma once
#include "Core/Events/Event.h"

class GUIElement {
public:
	GUIElement() {};
	virtual void onNotify(Event& newEvent) {};
	virtual void draw() = 0;
};