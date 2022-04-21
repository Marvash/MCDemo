#include "WindowException.h"


WindowException::WindowException() : Exception(std::string("")) {

}

WindowException::WindowException(std::string& message) : Exception(message) {

}