#pragma once
#include "Exception.h"

class GameLogicException : public Exception
{
public:
	GameLogicException() : Exception("Generic game logic exception") {};
	GameLogicException(std::string& message) : Exception(message) {};
};