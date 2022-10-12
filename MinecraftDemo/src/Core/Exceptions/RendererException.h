#pragma once
#include "Exception.h"

class RendererException : public Exception
{
public:
	RendererException();
	RendererException(std::string& message);
};