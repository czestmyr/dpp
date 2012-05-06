#include "ArgumentException.h"

using namespace std;

namespace Arglib {

ArgumentException::ArgumentException(const string& exceptionMessage): message(exceptionMessage) {}

ArgumentException::~ArgumentException() throw() {}

const char* ArgumentException::what() const throw() {
	return message.c_str();
}

} // End namespace Arglib

