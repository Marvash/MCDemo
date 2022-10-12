#pragma once
#include "Event.h"
#include "EventTypeEnum.h"
class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(double& posX, double& posY);
	double m_posX;
	double m_posY;
};

