#include <cstdlib>
#include "IntType.h"
#include "../values/Values.h"
#include "../StringParser.h"

using namespace std;

namespace Arglib {

IntType::IntType() {
	hasLowBound = false;
	hasHighBound = false;
	parameterName = "INTEGER";
}

void IntType::setLowBound(int bound) {
	hasLowBound = true;
	lowBound = bound;
}

void IntType::setHighBound(int bound) {
	hasHighBound = true;
	highBound = bound;
}

Value* IntType::fromString(const string& argument) const {
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
		argParser.raiseException("No numbers in the integer");
	}
	size_t numbersEnd = argParser.getPosition();
	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		argParser.raiseException("Trailing characters in an integer");
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
		argParser.raiseException("Integer value out of bounds");
	}
	if (hasLowBound && intValue < lowBound) {
		argParser.raiseException("Integer value out of bounds");
	}

	// Set and return the correct value
	IntValue* val = new IntValue(intValue);
	return val;
}

Type* IntType::clone() const {
	return new IntType(*this);
}

} // End namespace Arglib

