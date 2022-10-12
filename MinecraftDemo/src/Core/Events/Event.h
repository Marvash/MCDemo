#pragma once
#include "EventTypeEnum.h"
class Event
{
public:
	Event(EventType type);

	EventType getEventType();
	bool isHandled() const;
	void setHandled();
private:
	EventType eventType;
	bool m_handled;
};

