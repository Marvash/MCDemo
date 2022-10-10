#pragma once
#include "Core/Textures/ImageTexture2D.h"
#include "ItemIdEnum.h"
#include <glm/common.hpp>

class IItem;
class CoreServiceLocator;
class ItemGenerator;

class ItemHandle {

	friend class ItemGenerator;

public:
	~ItemHandle();
	ImageTexture2D* getItemIcon();
	void itemPrimaryActionUpdate(CoreServiceLocator* coreServiceLocator);
	void itemPrimaryActionEnd(CoreServiceLocator* coreServiceLocator);
	void itemSecondaryActionUpdate(CoreServiceLocator* coreServiceLocator);
	void itemSecondaryActionEnd(CoreServiceLocator* coreServiceLocator);
	ItemId getItemId();
	float getItemBreakScalingFactor();
	int getItemMaxStackCount();
	bool isCompatibleWith(ItemHandle* target);
	int getItemCount();
	void addToItemCount(unsigned int value);
	void subtractToItemCount(unsigned int value);
	bool isNullItem();
	void swapHandle(ItemHandle* item);
	int mergeWithHandle(ItemHandle* item);
	void setNull();
	void changeItem(ItemId itemId, unsigned int count = 1);

protected:
	static ItemGenerator* m_itemGenerator;
	IItem* m_wrappedItem;
	IItem* m_nullItem;
	int m_itemCount;

private:
	ItemHandle();
	void setWrappedItemInstance(IItem* wrappedItem, unsigned int count);
	void setNullItemInstance(IItem* nullItem);
	void deleteCurrentWrappedItem();
};