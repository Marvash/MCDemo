#include "CoreServiceLocator.h"

CoreServiceLocator::CoreServiceLocator() {

}

InputManager* CoreServiceLocator::getInput() {
	return m_input;
}

Window* CoreServiceLocator::getWindow() {
	return m_window;
}

Graphics* CoreServiceLocator::getGraphics() {
	return m_graphics;
}

ApplicationManager* CoreServiceLocator::getApplicationManager() {
	return m_applicationManager;
}

MovementSystem* CoreServiceLocator::getMovementSystem() {
	return m_movementSystem;
}

World* CoreServiceLocator::getWorld() {
	return m_world;
}

CameraSystem* CoreServiceLocator::getCameraSystem() {
	return m_cameraSystem;
}

void CoreServiceLocator::provide(InputManager* input) {
	m_input = input;
}

void CoreServiceLocator::provide(Window* window) {
	m_window = window;
}

void CoreServiceLocator::provide(Graphics* renderer) {
	m_graphics = renderer;
}

void CoreServiceLocator::provide(ApplicationManager* applicationManager) {
	m_applicationManager = applicationManager;
}

void CoreServiceLocator::provide(MovementSystem* movementSystem) {
	m_movementSystem = movementSystem;
}

void CoreServiceLocator::provide(World* world) {
	m_world = world;
}

void CoreServiceLocator::provide(CameraSystem* cameraSystem) {
	m_cameraSystem = cameraSystem;
}