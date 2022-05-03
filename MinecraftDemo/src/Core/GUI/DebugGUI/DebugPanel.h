#pragma once
#include "Core/GUI/GUIElement.h"
#include "imgui/imgui.h"
#include <glm/glm.hpp>

class DebugPanel : public GUIElement {
public:
	DebugPanel();
	void draw() override;
	void setDeltaTime(double deltaTime);
	void setPlayerPosition(glm::vec3& position);

private:
	ImGuiWindowFlags m_windowFlags;
	double m_deltaTime;
	glm::vec3 m_playerPosition;
};