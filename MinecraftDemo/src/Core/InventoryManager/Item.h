#pragma once

class Item {
public:
	enum class ItemType {
		CUBE
	};

	Item(ItemType type, unsigned int count);
	ItemType getItemType();
	unsigned int getCount();
	void setCount(unsigned int count);
protected:
	ItemType m_type;
	unsigned int m_count;
};