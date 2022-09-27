#include "DefaultItem.h"
#include "Core/Services/CoreServiceLocator.h"

DefaultItem::DefaultItem(IItem* wrappedItem) :
	ItemDecorator(wrappedItem) {

}

void DefaultItem::itemPrimaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
	Block* targetBlock = player->getFirstNonEmptyBlock();
	if (targetBlock != nullptr) {
		double deltaTime = coreServiceLocator->getApplicationManager()->getDeltaTime();
		//BOOST_LOG_TRIVIAL(info) << "UPDATING BREAKING CONTEXT";
		coreServiceLocator->getBlockManager()->updateBlockBreakingContext(deltaTime, targetBlock, item);
	}
	ItemDecorator::itemPrimaryActionUpdate(item, coreServiceLocator);
}

void DefaultItem::itemPrimaryActionEnd(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	//BOOST_LOG_TRIVIAL(info) << "STOPPING BREAKING CONTEXT 1";
	coreServiceLocator->getBlockManager()->stopBlockBreakingContext();
	ItemDecorator::itemPrimaryActionEnd(item, coreServiceLocator);
}