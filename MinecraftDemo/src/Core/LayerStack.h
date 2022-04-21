#pragma once
#include "Layer/Layer.h"
#include <vector>
#include <algorithm>

class LayerStack {
public:
	LayerStack();
	~LayerStack();

	void addLayer(Layer* layer);
	void addOverlay(Layer* layer);
	void removeLayer(Layer* layer);
	void removeOverlay(Layer* layer);

	void update();
	void onNotify(Event& newEvent);

private:
	std::vector<Layer*> m_layers;
	std::vector<Layer*>::iterator m_layerInsertIt;
};