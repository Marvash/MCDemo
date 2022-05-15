#include "DebugPanel.h"
#include <boost/log/trivial.hpp>

DebugPanel::DebugPanel() :
    GUIElement(),
    m_windowFlags(0),
	m_deltaTime(0.0),
    m_playerPosition(0.0f, 0.0f, 0.0f),
    m_playerLook(0.0f, 0.0f, 0.0f),
    m_selectedCubeName("None"),
    m_targetCubeName("None") {
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
    ImGui::SetNextWindowSize(ImVec2(380, 160), ImGuiCond_None);
    ImGui::SetNextWindowBgAlpha(0.4);
	ImGui::Begin("", nullptr, m_windowFlags);
    //ImGuiStyle* style = &ImGui::GetStyle();
    //ImGui::Text("Framerate: %d", (int)(1.0 / m_deltaTime));
    ImGui::Text("Framerate: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Player position:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "X: %.3f", m_playerPosition.x);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), "Y: %.3f", m_playerPosition.y);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 0.0, 1.0, 1.0), "Z: %.3f", m_playerPosition.z);
    ImGui::Text("Player look:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "X: %.3f", m_playerLook.x);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), "Y: %.3f", m_playerLook.y);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 0.0, 1.0, 1.0), "Z: %.3f", m_playerLook.z);
    ImGui::Text("Player velocity:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "X: %.3f", m_playerVelocity.x);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), "Y: %.3f", m_playerVelocity.y);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0, 0.0, 1.0, 1.0), "Z: %.3f", m_playerVelocity.z);
    ImGui::Text("Selected Cube: %s", m_selectedCubeName.c_str());
    ImGui::Text("Target Cube: %s", m_targetCubeName.c_str());
    ImGui::End();
}

void DebugPanel::setDeltaTime(double deltaTime) {
	m_deltaTime = deltaTime;
}

void DebugPanel::setPlayerPosition(glm::vec3& position) {
    m_playerPosition = position;
}

void DebugPanel::setPlayerLook(glm::vec3& look) {
    m_playerLook = look;
}

void DebugPanel::setSelectedCubeName(std::string& cubeName) {
    m_selectedCubeName = cubeName;
}

void DebugPanel::setTargetCubeName(std::string& cubeName) {
    m_targetCubeName = cubeName;
}

void DebugPanel::setPlayerVelocity(glm::vec3& velocity) {
    m_playerVelocity = velocity;
}