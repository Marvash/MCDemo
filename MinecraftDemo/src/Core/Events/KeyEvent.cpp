#include "KeyEvent.h"

KeyEvent::KeyEvent(InputKey key, InputAction action) : Event(EventType::KEY_BUTTON),
	m_key(key),
	m_action(action) {

}
