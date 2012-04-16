#include "Integer.h"
#include "../Parser.h"  // Parsing functions

using namespace std;

Integer::Integer() {
	hasLowBound = false;
	hasHighBound = false;
}

void Integer::setLowBound(int bound) {
	hasLowBound = true;
	lowBound = bound;
}

void Integer::setHighBound(int bound) {
	hasHighBound = true;
	highBound = bound;
}

bool Integer::conforms(const string& argument) const {
	Parser argParser(argument);

	// Parse some whitespace, followed by a plus or minus sign and some
	// whitespace again. Then, parse numbers followed by trailing whitespace.
	argParser.parseMany(WHITESPACE);  //WHITESPACE constant in parser function header
	argParser.parseOne("+-");
	argParser.parseMany(WHITESPACE);
	
	// Fail if no numbers could be parsed
	if (argParser.parseMany(NUMBERS) == 0) {
		return false;
	}
	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
	  return false;
	}

	// TODO: Check for bound compliance
	
	return true;
}

Value Integer::fromString(const std::string& argument) const {
	// TODO: implement this
	return Value();
}

