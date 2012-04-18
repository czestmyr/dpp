#include <cstdlib>
#include "Integer.h"
#include "../StringParser.h"

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

Value Integer::fromString(const string& argument) const {
	Value val;

	StringParser argParser(argument);

	// Parse some whitespace, followed by a plus or minus sign and some
	// whitespace again. Then, parse numbers followed by trailing whitespace.
	argParser.parseMany(WHITESPACE);  //WHITESPACE constant in parser function header
	size_t signPosition = argParser.getPosition();
	argParser.parseOne("+-");
	argParser.parseMany(WHITESPACE);
	
	// Fail if no numbers could be parsed
	size_t numbersBegin = argParser.getPosition();
	if (argParser.parseMany(NUMBERS) == 0) {
		return val;
	}
	size_t numbersEnd = argParser.getPosition();
	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		return val;
	}

	// Parse the number itself
	string cleanedArgument;
       	if (argument[signPosition] == '-') {
		cleanedArgument = "-";
	}
	cleanedArgument += argument.substr(numbersBegin, numbersEnd);
	int intValue = atoi(cleanedArgument.c_str());

	// Check for bound compliance
	if (hasHighBound && intValue > highBound) {
		return val;
	}
	if (hasLowBound && intValue < lowBound) {
		return val;
	}

	// Set and return the correct value
	val.setInt(intValue);
	return val;
}

