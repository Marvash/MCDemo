#pragma once
#include "Core/Inventory/Item.h"
#include "Core/Inventory/InventoryManager.h"

class Recipe {
public:
	Recipe();
private:
	Item** m_recipe;
};