#include <cstdlib>
#include "FormatType.h"
#include "../src/values/Values.h"

using namespace std;
using namespace Arglib;

FormatType::FormatType() {	
	parameterName = "FORMAT";
}

FormatType::~FormatType() {
}

Value* FormatType::fromString(const string& argument) const {
	// Set and return the correct value
	StringValue* val = new StringValue(argument);
	return val;
}

Type* FormatType::clone() const {
	return new FormatType(*this);
}

