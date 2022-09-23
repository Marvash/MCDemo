#pragma once
#include "Core/Services/Block/BlockFaceEnum.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

class AtlasElementTexIndex {
public:
	AtlasElementTexIndex();
	void setFaceTexIndex(BlockFace face, int index);
	int getTexIndexByFace(BlockFace face);
private:
	std::map<BlockFace, int> m_faceToTexIndex;
};