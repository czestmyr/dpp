#include <cstdlib>
#include "BoolType.h"
#include "../values/Values.h"
#include "../StringParser.h"

using namespace std;

namespace Arglib {

BoolType::BoolType() {
	parameterName = "BOOLEAN";
}

Value* BoolType::fromString(const string& argument) const {

	StringParser argParser(argument);
	
	argParser.parseMany(WHITESPACE);  //WHITESPACE constant in parser function header
	
	// parse single word from the parameter
	size_t keyWordBegin = argParser.getPosition();
	argParser.parseMany(LETTERS);
	size_t keyWordEnd = argParser.getPosition();

	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		argParser.raiseException("There is more than one keyword in boolean parameter: " + argument);
	}

	string keyWord = argument.substr(keyWordBegin, keyWordEnd);
	if ((keyWord != "true") && (keyWord != "false")) {
		argParser.raiseException("The given keyword in parameter isn't \"true\" nor \"false\". It's: " + argument);
	}
	// now the keyWord is either true or false
	bool isKeyWordTrue = (keyWord == "true"); 

	// Set and return the correct value
	BoolValue* val = new BoolValue(isKeyWordTrue);
	return val;
}

Type* BoolType::clone() const {
	return new BoolType(*this);
}

} // End namespace Arglib

