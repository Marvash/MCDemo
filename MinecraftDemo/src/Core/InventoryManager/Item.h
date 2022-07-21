#pragma once

class Item {
public:
	enum class ItemType {
		NONE,
		BLOCK
	};

	Item();
	ItemType getItemType();
protected:
	ItemType m_type;

};