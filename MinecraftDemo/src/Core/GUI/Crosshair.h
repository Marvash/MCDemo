#pragma once
#include "Core/GUI/GUIElement.h"
#include "imgui/imgui.h"
#include "Core/Services/CoreServiceLocator.h"
#include "Core/Services/Graphics/Graphics.h"
#include <glm/glm.hpp>
#include <string>

class Crosshair : public GUIElement {
public:
	Crosshair(CoreServiceLocator* coreServiceLocator);
	void draw() override;

private:
	ImGuiWindowFlags m_windowFlags;
	CoreServiceLocator* m_coreServiceLocator;
	Graphics* m_graphics;
};