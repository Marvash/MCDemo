#include "Layer.h"

Layer::Layer(std::string layerName) : m_layerName(layerName) {

}

const std::string& Layer::getLayerName() const {
	return m_layerName;
}

Layer::~Layer() {

}