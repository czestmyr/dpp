#include "BoolValue.h"
#include "../ArgumentException.h"

//TODO: Add proper information to this exception!
template <> bool ValueHandle::getValue<bool>() {
		if( valuePtr == NULL ) {
			throw ArgumentException("No parametr were added to this option.");
		}

		BoolValue* boolValue = dynamic_cast<BoolValue*>(valuePtr);
		if( boolValue == NULL ) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return boolValue->get();

};

