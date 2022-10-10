#include "Core.h"

Core::Core() : 
	m_stateChangeRequested(false), 
	m_shouldExitApplication(false), 
	m_nextState(nullptr),
	m_currentLayerStack(nullptr),
	m_coreSM(new StateMachine<CoreState>()),
	m_serviceLocator(new CoreServiceLocator()),
	m_eventDispatcher(new CoreEventDispatcher()), 
	m_biomeLibrary(new BiomeLibrary(m_eventDispatcher)),
	m_atlas(new Atlas(m_eventDispatcher)),
	m_renderer(new Renderer(m_eventDispatcher)),
	m_chunkManager(new ChunkManager(m_eventDispatcher)),
	m_blockLibrary(new BlockLibrary(m_serviceLocator)),
	m_itemLibrary(new ItemLibrary()),
	m_craftingRecipeLibrary(new CraftingRecipeLibrary()) {
	m_serviceLocator->provide(new Window(m_eventDispatcher));
	m_serviceLocator->provide(new InputManager(m_eventDispatcher));
	m_serviceLocator->provide(new ApplicationManager(this, m_eventDispatcher));
	m_serviceLocator->provide(new MovementSystem(m_eventDispatcher));
	m_serviceLocator->provide(new World(m_eventDispatcher));
	m_serviceLocator->provide(new Graphics(m_eventDispatcher));
	m_serviceLocator->provide(new CameraSystem(m_eventDispatcher));
	m_serviceLocator->provide(new GameObjectManager(m_eventDispatcher));
	m_serviceLocator->provide(new AtlasService(m_eventDispatcher));
	m_serviceLocator->provide(new BiomeService(m_eventDispatcher));
	m_serviceLocator->provide(new ItemGenerator(m_eventDispatcher));
	m_serviceLocator->provide(new BlockManager(m_eventDispatcher));
	m_serviceLocator->provide(new Inventory(m_eventDispatcher));
	m_serviceLocator->provide(new CraftingTable(m_eventDispatcher));
	m_eventDispatcher->addSubService(m_serviceLocator->getWindow());
	m_eventDispatcher->addSubService(m_renderer);
	m_eventDispatcher->addSubService(m_serviceLocator->getInput());
	m_eventDispatcher->addSubService(m_serviceLocator->getApplicationManager());
	m_eventDispatcher->addSubService(m_serviceLocator->getWorld());
}

CoreServiceLocator* Core::getServiceLocator() {
	return m_serviceLocator;
}

void Core::addState(ApplicationCoreState* newState) {
	this->m_coreSM->add(newState);
	if (m_nextState == nullptr) {
		m_nextState = newState;
	}
}

void Core::setNextState(CoreState nextStateId) {
	ApplicationCoreState* nextState = static_cast<ApplicationCoreState*>(m_coreSM->getState(nextStateId));
	if(nextState == nullptr) {
		throw Exception("Requested next state is not mapped");
	}
	setNextState(nextState);
}

void Core::setNextState(ApplicationCoreState* state) {
	m_nextState = state;
	m_stateChangeRequested = true;
}

void Core::initializeCoreServices() {
	m_serviceLocator->getWindow()->init();
	m_biomeLibrary->init();
	m_atlas->init();
	m_renderer->setAtlas(m_atlas);
	m_renderer->setBiomeManager(m_biomeLibrary);
	m_renderer->init();
	m_itemLibrary->init(m_renderer, m_biomeLibrary, m_atlas, m_blockLibrary);
	m_serviceLocator->getBlockManager()->init(m_blockLibrary);
	m_serviceLocator->getItemGenerator()->init(m_itemLibrary);
	m_serviceLocator->getInventory()->init(m_serviceLocator->getItemGenerator());
	m_chunkManager->init(m_biomeLibrary, m_atlas, m_serviceLocator->getBlockManager());
	m_serviceLocator->getMovementSystem()->init(m_chunkManager);
	m_serviceLocator->getWorld()->init(m_chunkManager, m_serviceLocator->getCameraSystem());
	m_serviceLocator->getGraphics()->init(m_renderer);
	m_serviceLocator->getGraphics()->setCameraRenderingData(m_serviceLocator->getCameraSystem()->getCameraRenderingData());
	m_serviceLocator->getAtlasService()->init(m_atlas);
	m_serviceLocator->getBiomeService()->init(m_biomeLibrary);
	m_craftingRecipeLibrary->init(m_serviceLocator->getItemGenerator());
	m_serviceLocator->getCraftingTable()->init(m_craftingRecipeLibrary, m_serviceLocator->getItemGenerator());
}

void Core::shutdownCoreServices() {
	m_renderer->deinit();
	m_serviceLocator->getWindow()->deinit();
}

Core::~Core() {
	delete m_coreSM;
	delete m_eventDispatcher;
	if (m_serviceLocator->getInput() != nullptr)
		delete m_serviceLocator->getInput();
	if (m_renderer != nullptr)
		delete m_renderer;
	if (m_serviceLocator->getWindow() != nullptr)
		delete m_serviceLocator->getWindow();
	if (m_serviceLocator->getApplicationManager() != nullptr)
		delete m_serviceLocator->getApplicationManager();
	if (m_serviceLocator->getMovementSystem() != nullptr)
		delete m_serviceLocator->getMovementSystem();
	if (m_serviceLocator->getWorld() != nullptr)
		delete m_serviceLocator->getWorld();
	delete m_serviceLocator;
}

void Core::run() {
	try {
		initializeCoreServices();
		double deltaTime, lastFrameTime = 0.0;
		//Main application loop
		while (true) {
			transitionToNextState();
			// Main application exit method
			if (m_shouldExitApplication)
				break;
			// Reset last frame time after state change
			lastFrameTime = glfwGetTime();
			// Update loop
			// If state change requested exit update loop
			while (!m_stateChangeRequested) {
				double currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrameTime;
				lastFrameTime = currentFrame;
				update(deltaTime);
			}
		}
		// The following line is necessary to call exit function for last state
		m_coreSM->setCurrentState(nullptr);
		shutdownCoreServices();
	}
	catch (Exception& e) {
		BOOST_LOG_TRIVIAL(fatal) << e.getErrorString();
	}
}

void Core::update(double& dt) {
	m_serviceLocator->getApplicationManager()->m_deltaTime = dt;

	m_serviceLocator->getApplicationManager()->m_time += dt;

	m_serviceLocator->getMovementSystem()->update(dt);

	m_serviceLocator->getInput()->dispatchInputEvents();

	m_serviceLocator->getGameObjectManager()->update();

	m_currentLayerStack->update();
	
	m_renderer->draw();

	m_serviceLocator->getInput()->resetInputManager();
	m_serviceLocator->getWindow()->updateWindow();
}

void Core::setCurrentLayerStack(LayerStack* layerStack) {
	m_currentLayerStack = layerStack;
	m_eventDispatcher->setLayerStack(m_currentLayerStack);
}

void Core::transitionToNextState() {
	if (m_nextState == nullptr) {
		throw Exception("Next application state is invalid");
	}
	// Reset state change request
	m_stateChangeRequested = false;
	// Change state
	m_coreSM->setCurrentState(m_nextState);
	// Set current state layer stack
	setCurrentLayerStack(m_nextState->getLayerStack());
}

void Core::setApplicationExitFlag() {
	m_shouldExitApplication = true;
}