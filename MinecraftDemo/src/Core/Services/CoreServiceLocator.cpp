#include "CoreServiceLocator.h"

CoreServiceLocator::CoreServiceLocator() {

}

InputManager* CoreServiceLocator::getInput() {
	return m_input;
}

Window* CoreServiceLocator::getWindow() {
	return m_window;
}

Graphics* CoreServiceLocator::getGraphics() {
	return m_graphics;
}

ApplicationManager* CoreServiceLocator::getApplicationManager() {
	return m_applicationManager;
}

MovementSystem* CoreServiceLocator::getMovementSystem() {
	return m_movementSystem;
}

World* CoreServiceLocator::getWorld() {
	return m_world;
}

CameraSystem* CoreServiceLocator::getCameraSystem() {
	return m_cameraSystem;
}

GameObjectManager* CoreServiceLocator::getGameObjectManager() {
	return m_gameObjectManager;
}

AtlasService* CoreServiceLocator::getAtlasService() {
	return m_atlasService;
}

BiomeService* CoreServiceLocator::getBiomeService() {
	return m_biomeService;
}

Inventory* CoreServiceLocator::getInventory() {
	return m_inventory;
}

ItemGenerator* CoreServiceLocator::getItemGenerator() {
	return m_itemGenerator;
}

BlockManager* CoreServiceLocator::getBlockManager() {
	return m_blockManager;
}

CraftingTable* CoreServiceLocator::getCraftingTable() {
	return m_craftingTable;
}

void CoreServiceLocator::provide(InputManager* input) {
	m_input = input;
}

void CoreServiceLocator::provide(Window* window) {
	m_window = window;
}

void CoreServiceLocator::provide(Graphics* renderer) {
	m_graphics = renderer;
}

void CoreServiceLocator::provide(ApplicationManager* applicationManager) {
	m_applicationManager = applicationManager;
}

void CoreServiceLocator::provide(MovementSystem* movementSystem) {
	m_movementSystem = movementSystem;
}

void CoreServiceLocator::provide(World* world) {
	m_world = world;
}

void CoreServiceLocator::provide(CameraSystem* cameraSystem) {
	m_cameraSystem = cameraSystem;
}

void CoreServiceLocator::provide(GameObjectManager* gameObjectManager) {
	m_gameObjectManager = gameObjectManager;
}

void CoreServiceLocator::provide(AtlasService* atlasService) {
	m_atlasService = atlasService;
}

void CoreServiceLocator::provide(BiomeService* biomeService) {
	m_biomeService = biomeService;
}

void CoreServiceLocator::provide(Inventory* inventoryService) {
	m_inventory = inventoryService;
}

void CoreServiceLocator::provide(ItemGenerator* itemGeneratorService) {
	m_itemGenerator = itemGeneratorService;
}

void CoreServiceLocator::provide(BlockManager* blockManagerService) {
	m_blockManager = blockManagerService;
}

void CoreServiceLocator::provide(CraftingTable* craftingTable) {
	m_craftingTable = craftingTable;
}