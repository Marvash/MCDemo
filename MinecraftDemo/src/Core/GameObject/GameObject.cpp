#include "GameObject.h"

unsigned int GameObject::nextId = 0;

GameObject::GameObject() : m_id(nextId++), m_position(glm::vec3(0.0f, 0.0f, 0.0f)) {

}

void GameObject::onNotify(Event& newEvent) {

}