#include "ArgumentException.h"

using namespace std;

namespace Arglib {

ArgumentException::ArgumentException(const string& exceptionMessage): message(exceptionMessage) {}

ArgumentException::~ArgumentException() throw() {}

void ArgumentException::prepend(const std::string& moreInfo) {
	message = moreInfo + message;
}

const char* ArgumentException::what() const throw() {
	return message.c_str();
}

} // End namespace Arglib

