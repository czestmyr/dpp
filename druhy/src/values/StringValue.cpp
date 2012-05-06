#include "StringValue.h"
#include "../ArgumentException.h"

using namespace std;

namespace Arglib {

//TODO: Add proper information to this exception!
template <>
string ValueHandle::getValue<string>() {
		if( valuePtr == NULL ) {
			throw ArgumentException("No parametr were added to this option.");
		}

		StringValue* stringValue = dynamic_cast<StringValue*>(valuePtr);
		if( stringValue == NULL ) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return stringValue->get();

};

} // End namespace Arglib

