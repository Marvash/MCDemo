#pragma once
#include "Core/GUI/GUIElement.h"
#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <string>

class DebugPanel : public GUIElement {
public:
	DebugPanel();
	void draw() override;
	void setDeltaTime(double deltaTime);
	void setPlayerPosition(glm::vec3& position);
	void setPlayerLook(glm::vec3& look);
	void setPlayerVelocity(glm::vec3& velocity);
	void setSelectedCubeName(std::string& cubeName);
	void setTargetCubeName(std::string& cubeName);

private:
	ImGuiWindowFlags m_windowFlags;
	double m_deltaTime;
	glm::vec3 m_playerPosition;
	glm::vec3 m_playerLook;
	glm::vec3 m_playerVelocity;
	std::string m_selectedCubeName;
	std::string m_targetCubeName;
};