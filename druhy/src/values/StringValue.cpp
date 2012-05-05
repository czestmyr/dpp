#include "StringValue.h"
#include "../ArgumentException.h"

using namespace std;

//TODO: Add proper information to this exception!
template <>
string ValueHandle::getValue<string>() {
		StringValue* stringValue = dynamic_cast<StringValue*>(valuePtr);
		if( stringValue == NULL ) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return stringValue->get();

};

