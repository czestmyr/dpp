#include "IntValue.h"
#include "../ArgumentException.h"

namespace Arglib {

template <>
int ValueHandle::getValue<int>() {
	if (isEmpty()) {
		throw ArgumentException("No parameter specified.");
	}

	IntValue* intValue = dynamic_cast<IntValue*>(valuePtr);
	if (intValue == NULL) {
		throw ArgumentException("This option has a different type than specified in template function");
	}
	return intValue->get();

};

} // End namespace Arglib

