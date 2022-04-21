#include "Core.h"

Core::Core() : 
	m_stateChangeRequested(false), 
	m_shouldExitApplication(false), 
	m_nextState(nullptr),
	m_currentLayerStack(nullptr) {
	m_coreSM = new StateMachine<CoreState>();
	m_serviceLocator = new CoreServiceLocator();
	m_eventDispatcher = new CoreEventDispatcher();
	m_serviceLocator->provide(new Window(m_eventDispatcher));
	m_serviceLocator->provide(new InputManager(m_eventDispatcher));
	m_serviceLocator->provide(new Renderer(m_eventDispatcher));
	m_serviceLocator->provide(new ApplicationManager(this, m_eventDispatcher));
	m_eventDispatcher->addSubService(m_serviceLocator->getRenderer());
	m_eventDispatcher->addSubService(m_serviceLocator->getWindow());
	m_eventDispatcher->addSubService(m_serviceLocator->getInput());
	m_eventDispatcher->addSubService(m_serviceLocator->getApplicationManager());
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
	m_serviceLocator->getRenderer()->init();
}

Core::~Core() {
	delete m_coreSM;
	delete m_eventDispatcher;
	if (m_serviceLocator->getInput() != nullptr)
		delete m_serviceLocator->getInput();
	if (m_serviceLocator->getRenderer() != nullptr)
		delete m_serviceLocator->getRenderer();
	if (m_serviceLocator->getWindow() != nullptr)
		delete m_serviceLocator->getWindow();
	if (m_serviceLocator->getApplicationManager() != nullptr)
		delete m_serviceLocator->getApplicationManager();
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
	}
	catch (Exception& e) {
		BOOST_LOG_TRIVIAL(fatal) << e.getError();
	}
}

void Core::update(double& dt) {
	//BOOST_LOG_TRIVIAL(trace) << dt;
	m_serviceLocator->getApplicationManager()->m_deltaTime = dt;

	m_serviceLocator->getInput()->dispatchInputEvents();

	m_currentLayerStack->update();

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