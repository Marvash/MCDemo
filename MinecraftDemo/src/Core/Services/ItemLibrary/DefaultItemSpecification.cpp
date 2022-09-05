#include "DefaultItemSpecification.h"
#include "Core/Services/CoreServiceLocator.h"

DefaultItemSpecification::DefaultItemSpecification(ItemId itemId, ImageTexture2D* itemIcon) : 
	ItemSpecification(itemId, itemIcon, MAX_DEFAULT_ITEM_STACK) {

}

void DefaultItemSpecification::performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) {
	Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
	Cube* targetCube = player->getFirstSolidCube();
	if (targetCube != nullptr) {
		CubeId targetCubeId = targetCube->getCubeId();
		coreServiceLocator->getWorld()->destroyBlock(targetCube);
		coreServiceLocator->getInventory()->addItem(Cube::getItemId(targetCubeId), 1);
	}
}

void DefaultItemSpecification::performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) {

}