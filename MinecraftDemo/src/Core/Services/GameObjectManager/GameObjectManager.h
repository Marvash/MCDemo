#pragma once
#include "Core/Services/CoreService.h"
#include "Core/GameObject/GameObject.h"
#include "Core/Player/Player.h"
#include "Core/GameObject/GameObjectTypeEnum.h"
#include <map>

class GameObjectManager : public CoreService {
public:
	GameObjectManager(CoreEventDispatcher* coreEventDispatcher);
	void onNotify(Event& newEvent) override;
	Player* getPlayer();
	void setPlayerId(unsigned int playerId);
	GameObject* getGameObject(unsigned int id);
	void registerEntity(GameObject* gameObject);
	void update();
	void sendEvent(Event& toSend);

private:
	std::map<unsigned int, GameObject*> m_allEntities;
	std::map<unsigned int, GameObject*> m_staticEntities;
	std::map<unsigned int, GameObject*> m_dynamicEntities;

	unsigned int m_playerId;
};