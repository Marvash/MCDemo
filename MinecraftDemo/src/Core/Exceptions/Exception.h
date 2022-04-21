#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(std::string message);

	std::string getError();

private:
	std::string message;
};

