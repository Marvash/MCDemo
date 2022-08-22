#include "PlaceableItemSpecification.h"
#include "Core/Services/CoreServiceLocator.h"

PlaceableItemSpecification::PlaceableItemSpecification(ItemId itemId, ImageTexture2D* itemIcon, CubeId cubeId) :
	ItemSpecification(itemId, itemIcon, MAX_PLACEABLE_ITEM_STACK),
	m_cubeId(cubeId) {

}

void PlaceableItemSpecification::performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) {
	Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
	Cube* targetCube = player->getFirstSolidCube();
	if (targetCube != nullptr) {
		CubeId targetCubeId = targetCube->getCubeId();
		coreServiceLocator->getWorld()->destroyBlock(targetCube);
		coreServiceLocator->getInventory()->addItem(Cube::getItemId(targetCubeId), 1);
	}
}

void PlaceableItemSpecification::performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) {
	Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
	Inventory* inventory = coreServiceLocator->getInventory();
	Cube* lastPlaceableCube = player->getLastPlaceableCube();
	if (lastPlaceableCube != nullptr) {
		coreServiceLocator->getWorld()->placeBlock(lastPlaceableCube, m_cubeId);
		inventory->decreaseItemCountInSlot(1, inventory->getItemBarSelectedSlotAbs());
	}
}