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
	if (argParser.parseExact(4,"true") != 4) {// && argParser.parseExact(5,"false") == 0 ) {
		argParser.raiseException("No true in the boolean: " + argument);
	}
	size_t keyWordEnd = argParser.getPosition();
	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		argParser.raiseException("Trailing characters in an boolean: =" + argument + "=");
	}
	// TODO: Explain properly what this does
	bool isTrueParsed = ((keyWordEnd-keyWordBegin) == 4); 

	// Set and return the correct value
	BoolValue* val = new BoolValue(isTrueParsed);
	return val;
}

Type* BoolType::clone() const {
	return new BoolType(*this);
}

