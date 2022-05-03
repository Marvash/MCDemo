#include "DebugPanel.h"

DebugPanel::DebugPanel() :
    GUIElement(),
    m_windowFlags(0),
	m_deltaTime(0.0),
    m_playerPosition(0.0f, 0.0f, 0.0f) {
    m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
    m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
    //m_windowFlags |= ImGuiWindowFlags_MenuBar;
    m_windowFlags |= ImGuiWindowFlags_NoMove;
    m_windowFlags |= ImGuiWindowFlags_NoResize;
    //m_windowFlags |= ImGuiWindowFlags_NoCollapse;
    //m_windowFlags |= ImGuiWindowFlags_NoNav;
    //m_windowFlags |= ImGuiWindowFlags_NoBackground;
    //m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    //m_windowFlags |= ImGuiWindowFlags_UnsavedDocument;
}

void DebugPanel::draw() {
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_None);
    ImGui::SetNextWindowSize(ImVec2(260, 60), ImGuiCond_None);
    ImGui::SetNextWindowBgAlpha(0.4);
	ImGui::Begin("", nullptr, m_windowFlags);
    //ImGuiStyle* style = &ImGui::GetStyle();
    //ImGui::Text("Framerate: %d", (int)(1.0 / m_deltaTime));
    ImGui::Text("Framerate: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Player position:");
    ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "X: %.3f", m_playerPosition.x);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), "Y: %.3f", m_playerPosition.y);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 0.0, 1.0, 1.0), "Z: %.3f", m_playerPosition.z);
	ImGui::End();
}

void DebugPanel::setDeltaTime(double deltaTime) {
	m_deltaTime = deltaTime;
}

void DebugPanel::setPlayerPosition(glm::vec3& position) {
    m_playerPosition = position;
}