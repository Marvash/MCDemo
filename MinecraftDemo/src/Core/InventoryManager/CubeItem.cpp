#include "CubeItem.h"

CubeItem::CubeItem(Cube::CubeId cubeId) :
	Item(ItemType::CUBE, 0),
	m_cubeId(cubeId) {

}

CubeItem::CubeItem(Cube::CubeId cubeId, unsigned int count) :
	Item(ItemType::CUBE, count),
	m_cubeId(cubeId) {

}

Cube::CubeId CubeItem::getCubeId() {
	return m_cubeId;
}