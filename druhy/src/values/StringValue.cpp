#include "StringValue.h"
#include "../ArgumentException.h"

using namespace std;

namespace Arglib {

//TODO: Add proper information to this exception!
template <>
string ValueHandle::getValue<string>() {
	if (isEmpty()) {
		throw ArgumentException("No parameter specified.");
	}

	StringValue* stringValue = dynamic_cast<StringValue*>(valuePtr);
	if( stringValue == NULL ) {
		throw ArgumentException("This option has a different type than specified in template function");
	}
	return stringValue->get();

};

} // End namespace Arglib

