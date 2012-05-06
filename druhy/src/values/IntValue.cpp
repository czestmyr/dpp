#include "IntValue.h"
#include "../ArgumentException.h"

namespace Arglib {

//TODO: Add proper information to this exception!
//TODO: change test valuePtr == NULL za isEmpty()
template <> int ValueHandle::getValue<int>() {
		if (valuePtr == NULL) {
			throw ArgumentException("No parametr were added to this option.");
		}

		IntValue* intValue = dynamic_cast<IntValue*>(valuePtr);
		if (intValue == NULL) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return intValue->get();

};

} // End namespace Arglib

