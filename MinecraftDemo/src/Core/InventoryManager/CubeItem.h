#pragma once
#include "Item.h"
#include "Core/Cube/Cube.h"

class CubeItem : public Item {
public:
	CubeItem(Cube::CubeId cubeId);
	CubeItem(Cube::CubeId cubeId, unsigned int count);
	Cube::CubeId getCubeId();
private:
	Cube::CubeId m_cubeId;
};