#include <cstdlib>
#include "FormatType.h"
#include "../src/values/Values.h"
// TODO: improve the inlcude chaing
using namespace std;

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

