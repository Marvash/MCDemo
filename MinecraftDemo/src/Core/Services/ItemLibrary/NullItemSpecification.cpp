#include "NullItemSpecification.h"

NullItemSpecification::NullItemSpecification(ItemId itemId, ImageTexture2D* itemIcon) : ItemSpecification(itemId, itemIcon, 0) {

}

void NullItemSpecification::performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) {

}

void NullItemSpecification::performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) {

}