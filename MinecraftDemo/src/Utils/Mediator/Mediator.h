#pragma once

template <typename T, typename E>
class Mediator {
public:
	virtual void notify(T* component, E event);
protected:
	Mediator();
};