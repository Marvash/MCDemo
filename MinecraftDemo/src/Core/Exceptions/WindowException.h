#pragma once
#include "Exception.h"

class WindowException : public Exception
{
public:
	WindowException();
	WindowException(std::string& message);
};

