#include "Event.h"


Event::Event(EventType type) : eventType(type), m_handled(false) {

}

EventType Event::getEventType() {
	return eventType;
}

bool Event::isHandled() const {
	return m_handled;
}
void Event::setHandled() {
	if (!m_handled) {
		m_handled = true;
	}
}