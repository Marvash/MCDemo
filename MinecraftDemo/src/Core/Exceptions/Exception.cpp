#include "Exception.h"


Exception::Exception(std::string message) : 
	std::exception(), 
	message(message) {

}

std::string Exception::getErrorString() {
	return message;
}