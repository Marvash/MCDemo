#include "RendererException.h"

RendererException::RendererException() : Exception(std::string("")) {

}

RendererException::RendererException(std::string& message) : Exception(message) {

}