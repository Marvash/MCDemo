#include "ToolItemSpecification.h"
#include "Core/Services/CoreServiceLocator.h"

ToolItemSpecification::ToolItemSpecification(ItemId itemId, ImageTexture2D* itemIcon) :
	ItemSpecification(itemId, itemIcon, MAX_TOOL_ITEM_STACK) {

}

void ToolItemSpecification::performItemPrimaryAction(CoreServiceLocator* coreServiceLocator) {
	Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
	Cube* targetCube = player->getFirstSolidCube();
	if (targetCube != nullptr) {
		CubeId targetCubeId = targetCube->getCubeId();
		coreServiceLocator->getWorld()->destroyBlock(targetCube);
		coreServiceLocator->getInventory()->addItem(Cube::getItemId(targetCubeId), 1);
	}
}

void ToolItemSpecification::performItemSecondaryAction(CoreServiceLocator* coreServiceLocator) {

}