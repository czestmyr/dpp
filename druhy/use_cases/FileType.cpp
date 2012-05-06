#include <cstdlib>
#include "FileType.h"
#include "../src/values/Values.h"
// TODO: improve the inlcude chaing
using namespace std;
using namespace Arglib;

FileType::FileType() {	
	parameterName = "FILE";
}

FileType::~FileType() {
}

Value* FileType::fromString(const string& argument) const {
	// Set and return the correct value
	StringValue* val = new StringValue(argument);
	return val;
}

Type* FileType::clone() const {
	return new FileType(*this);
}

