#pragma once
#include "Core/Services/ItemLibrary/Item.h"

class Crafting {
public:
	Crafting();
	~Crafting();
	const unsigned int CRAFTING_TABLE_SLOTS = 9;

private:
	Item** m_craftingTable;
	Item* m_craftingResult;
};