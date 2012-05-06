#include "BoolValue.h"
#include "../ArgumentException.h"

namespace Arglib {

template <>
bool ValueHandle::getValue<bool>() {
	if (isEmpty()) {
		throw ArgumentException("No parameter specified.");
	}

	BoolValue* boolValue = dynamic_cast<BoolValue*>(valuePtr);
	if( boolValue == NULL ) {
		throw ArgumentException("This option has a different type than specified in template function");
	}
	return boolValue->get();

};

} // End namespace Arglib

