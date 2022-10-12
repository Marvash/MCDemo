#include "GameObject.h"
#include "Core/Services/CoreServiceLocator.h"

unsigned int GameObject::nextId = 1;

GameObject::GameObject(CoreServiceLocator* coreServiceLocator, GameObjectType gameObjectType) :
	m_coreServiceLocator(coreServiceLocator), 
	m_id(nextId++), 
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_gameObjectType(gameObjectType) {
	m_coreServiceLocator->getGameObjectManager()->registerEntity(this);
}

void GameObject::setMovementComponent(MovementComponent* moveComp) {
	m_movementComponent = moveComp;
}

void GameObject::registerComponents() {
	if (m_movementComponent != nullptr) {
		m_coreServiceLocator->getMovementSystem()->registerObject(this, m_movementComponent);
	}
}

void GameObject::onNotify(Event& newEvent) {

}