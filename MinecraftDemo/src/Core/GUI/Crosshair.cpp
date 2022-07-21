#include "Crosshair.h"
#include <boost/log/trivial.hpp>

Crosshair::Crosshair(CoreServiceLocator* coreServiceLocator) : 
    GUIElement(coreServiceLocator),
    m_windowFlags(0),
    m_coreServiceLocator(coreServiceLocator),
    m_graphics(coreServiceLocator->getGraphics()) {
    m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
    m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
    m_windowFlags |= ImGuiWindowFlags_NoInputs;
    //m_windowFlags |= ImGuiWindowFlags_MenuBar;
    m_windowFlags |= ImGuiWindowFlags_NoMove;
    m_windowFlags |= ImGuiWindowFlags_NoResize;
    //m_windowFlags |= ImGuiWindowFlags_NoCollapse;
    //m_windowFlags |= ImGuiWindowFlags_NoNav;
    m_windowFlags |= ImGuiWindowFlags_NoBackground;
    //m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    //m_windowFlags |= ImGuiWindowFlags_UnsavedDocument;
}

void Crosshair::draw() {
    float halfViewportWidth = m_graphics->getViewportWidth() / 2.0f;
    float halfViewportHeight = m_graphics->getViewportHeight() / 2.0f;
    float halfWindowWidth = 75;
    float halfWindowHeight = 75;
    float halfCrosshairWidth = 2;
    float halfCrosshairHeight = 22;
    ImVec2 windowP0(halfViewportWidth - halfWindowWidth, halfViewportHeight - halfWindowHeight);
    ImVec2 windowP1(halfViewportWidth + halfWindowWidth, halfViewportHeight + halfWindowHeight);
    ImVec2 verticalTileP0(halfViewportWidth - halfCrosshairWidth, halfViewportHeight - halfCrosshairHeight);
    ImVec2 verticalTileP1(halfViewportWidth + halfCrosshairWidth, halfViewportHeight + halfCrosshairHeight);
    ImVec2 horizontalTileP0(halfViewportWidth - halfCrosshairHeight, halfViewportHeight - halfCrosshairWidth);
    ImVec2 horizontalTileP1(halfViewportWidth + halfCrosshairHeight, halfViewportHeight + halfCrosshairWidth);
    ImGui::SetNextWindowPos(windowP0, ImGuiCond_None);
    ImVec2 windowSize = ImVec2(halfWindowWidth * 2, halfWindowHeight * 2);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_None);
    ImGui::Begin("Crosshair", nullptr, m_windowFlags);
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(verticalTileP0, verticalTileP1, ImColor(210, 210, 210));
    drawList->AddRectFilled(horizontalTileP0, horizontalTileP1, ImColor(210, 210, 210));
    ImGui::End();
}