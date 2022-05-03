#pragma once
#include "Core/Events/Event.h"
#include <string>

class Layer {
public:
	Layer(std::string layerName = "Unnamed Layer");
	virtual ~Layer();

	virtual void onAdd() = 0;
	virtual void onRemove() = 0;
	virtual void update() = 0;
	virtual void onNotify(Event& newEvent) = 0;

	const std::string& getLayerName() const;
protected:
	std::string m_layerName;
};