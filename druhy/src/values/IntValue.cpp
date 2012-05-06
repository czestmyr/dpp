#include "IntValue.h"
#include "../ArgumentException.h"

namespace Arglib {

//TODO: Add proper information to this exception!
template <>
int ValueHandle::getValue<int>() {
	if (isEmpty()) {
		throw ArgumentException("No parametr were added to this option.");
	}

	IntValue* intValue = dynamic_cast<IntValue*>(valuePtr);
	if (intValue == NULL) {
		throw ArgumentException("Type defined with this option doesn't match type required by this function.");
	}
	return intValue->get();

};

} // End namespace Arglib

