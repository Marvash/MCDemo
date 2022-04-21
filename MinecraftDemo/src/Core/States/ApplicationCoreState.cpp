#include "ApplicationCoreState.h"

ApplicationCoreState::ApplicationCoreState(Core* core, CoreState id, std::string name) : State<CoreState>(id, name),
	m_core(core),
	m_layerStack(new LayerStack()) {
}

LayerStack* ApplicationCoreState::getLayerStack() {
	return m_layerStack;
}