#include <cstdlib>
#include "StringType.h"
#include "../values/Values.h"
#include "../values/StringValue.h"
#include "../StringParser.h"

using namespace std;

namespace Arglib {

StringType::StringType() {
	parameterName = "STRING";	
}

Value* StringType::fromString(const string& argument) const {
	// Set and return the correct value
	StringValue* val = new StringValue(argument);
	return val;
}

Type* StringType::clone() const {
	return new StringType(*this);
}

} // End namespace Arglib

