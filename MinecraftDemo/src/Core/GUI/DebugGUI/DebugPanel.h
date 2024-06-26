#pragma once
#include "Core/GUI/GUIElement.h"
#include "imgui/imgui.h"
#include "Core/Services/CoreServiceLocator.h"
#include <boost/log/trivial.hpp>
#include <glm/glm.hpp>
#include <string>

class DebugPanel : public GUIElement {
public:
	DebugPanel(CoreServiceLocator* coreServiceLocator);
	void draw() override;
	void setDeltaTime(double deltaTime);
	void setPlayerPosition(glm::vec3 position);
	void setPlayerLook(glm::vec3 look);
	void setPlayerVelocity(glm::vec3 velocity);
	void setSelectedItemName(std::string& itemName);
	void setTargetCubeName(std::string& cubeName);
	void setSelectedMovementModeName(std::string& modeName);

private:
	ImGuiWindowFlags m_windowFlags;
	double m_deltaTime;
	glm::vec3 m_playerPosition;
	glm::vec3 m_playerLook;
	glm::vec3 m_playerVelocity;
	std::string m_selectedItemName;
	std::string m_targetCubeName;
	std::string m_selectedMovementModeName;
};