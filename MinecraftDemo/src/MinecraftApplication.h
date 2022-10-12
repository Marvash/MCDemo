#pragma once
#include "Core/Application/Application.h"
#include "Core/States/QuitCoreState.h"
#include "Core/States/MainMenuCoreState.h"
#include "Core/States/GameCoreState.h"
#include "Core/States/InitCoreState.h"
#include <string>

class MinecraftApplication : public Application {
public:
	MinecraftApplication();
	~MinecraftApplication();

	void run() override;
};