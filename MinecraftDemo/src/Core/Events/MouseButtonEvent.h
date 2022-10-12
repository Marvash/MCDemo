#pragma once
#include "Event.h"
#include "EventTypeEnum.h"
#include "Core/Services/Input/InputEnums.h"
class MouseButtonEvent : public Event
{
public:
	MouseButtonEvent(InputMouseButton button, InputAction action);
	InputMouseButton m_button;
	InputAction m_action;
};