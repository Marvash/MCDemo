#include "PlaceableItem.h"
#include "Core/Services/CoreServiceLocator.h"

PlaceableItem::PlaceableItem(IItem* wrappedItem) :
	ItemDecorator(wrappedItem),
	m_lastPlacedTime(0.0f) {

}

// TODO: Services needed by this decorator could be stored into the shared specification (m_placeableItemSharedSpec)

void PlaceableItem::itemSecondaryActionUpdate(ItemHandle* item, CoreServiceLocator* coreServiceLocator) {
	float currentTime = coreServiceLocator->getApplicationManager()->getTime();
	if (m_lastPlacedTime == 0.0f || (currentTime - m_lastPlacedTime) >= m_placeableItemSharedSpec->getItemPlaceInterval()) {
		Player* player = coreServiceLocator->getGameObjectManager()->getPlayer();
		Block* lastEmptyBlock = player->getLastEmptyBlock();
		if (lastEmptyBlock != nullptr) {
			coreServiceLocator->getBlockManager()->changeBlock(lastEmptyBlock, m_placeableItemSharedSpec->getBlockId());
			lastEmptyBlock->getChunkRef()->forceChunkMeshUpdate();
			m_lastPlacedTime = currentTime;
			item->subtractToItemCount(1);
		}
	}
}