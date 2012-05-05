#include "IntValue.h"
#include "../ArgumentException.h"

//TODO: Add proper information to this exception!
template <> int ValueHandle::getValue<int>() {
		IntValue* intValue = dynamic_cast<IntValue*>(valuePtr);
		if( intValue == NULL ) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return intValue->get();

};

