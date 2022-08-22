#include "Crafting.h"

Crafting::Crafting() : 
	m_craftingTable(new Item*[CRAFTING_TABLE_SLOTS]),
	m_craftingResult(nullptr) {
	for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
		m_craftingTable[i] = nullptr;
	}
}

Crafting::~Crafting() {
	for (int i = 0; i < CRAFTING_TABLE_SLOTS; i++) {
		delete m_craftingTable[i];
	}
	delete m_craftingTable;
	delete m_craftingResult;
}