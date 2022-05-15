#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(CoreEventDispatcher* coreEventDispatcher) : 
	CoreService(coreEventDispatcher),
	m_playerId(0) {

}

Player* GameObjectManager::getPlayer() {
	return dynamic_cast<Player*>(m_allEntities[m_playerId]);
}

void GameObjectManager::setPlayerId(unsigned int playerId) {
	m_playerId = playerId;
}

void GameObjectManager::registerEntity(GameObject* gameObject) {
	m_allEntities.insert(std::make_pair(gameObject->m_id, gameObject));
	switch (gameObject->m_gameObjectType) {
		case GameObjectType::STATIC: {
			m_staticEntities.insert(std::make_pair(gameObject->m_id, gameObject));
			break;
		}
		case GameObjectType::DYNAMIC: {
			m_dynamicEntities.insert(std::make_pair(gameObject->m_id, gameObject));
			break;
		}
	}
}

GameObject* GameObjectManager::getGameObject(unsigned int id) {
	GameObject* gameObject = nullptr;
	if (m_allEntities.find(id) != m_allEntities.end()) {
		gameObject = m_allEntities[id];
	}
	return gameObject;
}

void GameObjectManager::update() {
	for (const std::pair<unsigned int, GameObject*> pair : m_allEntities)
	{
		if (pair.second == nullptr)
			continue;
		pair.second->update();
	}
}

void GameObjectManager::sendEvent(Event& toSend) {
	notify(toSend);
}

void GameObjectManager::onNotify(Event& newEvent) {
}