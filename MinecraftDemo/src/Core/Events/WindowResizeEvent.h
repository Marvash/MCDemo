#pragma once
#include "Event.h"
#include "EventTypeEnum.h"
class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(const unsigned int &windowWidth, const unsigned int &windowHeight);

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
};