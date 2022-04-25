#include "LayerStack.h"

LayerStack::LayerStack() : m_layerInsertIt(m_layers.begin()) {

}

LayerStack::~LayerStack() {

}

void LayerStack::addLayer(Layer* layer) {
	m_layerInsertIt = m_layers.insert(m_layerInsertIt, layer);
	layer->onAdd();
}

void LayerStack::addOverlay(Layer* layer) {
	m_layers.push_back(layer);
	layer->onAdd();
}

void LayerStack::removeLayer(Layer* layer) {
	std::vector<Layer*>::iterator toRemoveIt = std::find(m_layers.begin(), m_layers.end(), layer);
	if (toRemoveIt != m_layers.end()) {
		m_layers.erase(toRemoveIt);
		m_layerInsertIt--;
		layer->onRemove();
	}
}

void LayerStack::removeOverlay(Layer* layer) {
	std::vector<Layer*>::iterator toRemoveIt = std::find(m_layers.begin(), m_layers.end(), layer);
	if (toRemoveIt != m_layers.end()) {
		m_layers.erase(toRemoveIt);
		layer->onRemove();
	}
}

void LayerStack::update() {
	for (Layer* layer : m_layers) {
		layer->update();
	}
}

void LayerStack::onNotify(Event& newEvent) {
	for (std::vector<Layer*>::reverse_iterator layerIt = m_layers.rbegin(); layerIt != m_layers.rend(); ++layerIt) {
		(*layerIt)->onNotify(newEvent);
		if (newEvent.isHandled()) {
			return;
		}
	}
}