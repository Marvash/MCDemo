#pragma once
#include "Event.h"
#include "EventTypeEnum.h"
#include "Core/Services/Input/InputEnums.h"
class KeyEvent : public Event
{
public:
	KeyEvent(InputKey key, InputAction action);
	InputKey m_key;
	InputAction m_action;
};