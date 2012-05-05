#include <cstdlib>
#include "BoolType.h"
#include "../values/Values.h"
#include "../StringParser.h"

using namespace std;

BoolType::BoolType() {
}

Value* BoolType::fromString(const string& argument) const {

	StringParser argParser(argument);
	
	argParser.parseMany(WHITESPACE);  //WHITESPACE constant in parser function header
	
	// Fail if no numbers could be parsed
	size_t keyWordBegin = argParser.getPosition();
	argParser.parseMany(LETTERS);
	size_t keyWordEnd = argParser.getPosition();

	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		argParser.raiseException("There is more than one keyword in boolean argument: " + argument);
	}

	string keyWord = argument.substr(keyWordBegin,keyWordEnd);
	if ((keyWord != "true") && (keyWord != "false")) {
		argParser.raiseException("The given keyword is'nt \"true\" nor \"false\". It's: " + argument);
	}

	bool isKeyWordTrue = (keyWord == "true"); 

	// Set and return the correct value
	BoolValue* val = new BoolValue(isKeyWordTrue);
	return val;
}

Type* BoolType::clone() const {
	return new BoolType(*this);
}

