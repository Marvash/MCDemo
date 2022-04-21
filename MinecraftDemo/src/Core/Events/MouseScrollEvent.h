#pragma once
#include "Event.h"
#include "EventTypeEnum.h"
class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(double& offsetX, double& offsetY);
private:
	double m_offsetX;
	double m_offsetY;
};