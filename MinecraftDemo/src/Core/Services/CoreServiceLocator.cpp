#include "CoreServiceLocator.h"

CoreServiceLocator::CoreServiceLocator() {

}

InputManager* CoreServiceLocator::getInput() {
	return m_input;
}

Window* CoreServiceLocator::getWindow() {
	return m_window;
}

Renderer* CoreServiceLocator::getRenderer() {
	return m_renderer;
}

ApplicationManager* CoreServiceLocator::getApplicationManager() {
	return m_applicationManager;
}

void CoreServiceLocator::provide(InputManager* input) {
	this->m_input = input;
}

void CoreServiceLocator::provide(Window* window) {
	this->m_window = window;
}

void CoreServiceLocator::provide(Renderer* renderer) {
	this->m_renderer = renderer;
}

void CoreServiceLocator::provide(ApplicationManager* applicationManager) {
	this->m_applicationManager = applicationManager;
}
