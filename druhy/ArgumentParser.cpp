#include "ArgumentParser.h"
#include "StringParser.h"

// TODO: Remove this before handing in
#include <iostream>

using namespace std;

ArgumentParser::ArgumentParser(): allRegular(false) {}

bool ArgumentParser::parse(int argc, char* argv[]) {
	int argIndex = 1;  // The zeroth argument is the name of the executable
	while (argIndex < argc) {
		string argument(argv[argIndex]);
		ArgumentType argType = determineType(argument);

		switch (argType) {
			case REGULAR_ARGUMENT:
				// Save the argument somewhere together with it's information
				std::cout << argument << " is a regular argument." << std::endl;
			break;
			case SHORT_OPTION:
				// Parse the short option
				std::cout << argument << " is a short option." << std::endl;
			break;
			case LONG_OPTION:
				// Parse the long option
				std::cout << argument << " is a long option." << std::endl;
			break;
			default:
				// This shouldn't happen
				return false;
		}

		argIndex++;
	}

	// If we got here, the arguments were parsed successfully.
	return true;
}

ArgumentParser::ArgumentType ArgumentParser::determineType(const std::string& argument) {
	// If we are past the double-hyphen, all arguments are regular
	if (allRegular) {
		return REGULAR_ARGUMENT;
	}

	StringParser parser(argument);

	// Otherwise, the argument type is determined by the number of leading hyphens
	int leadingHyphens = parser.parseMany("-");
	if (leadingHyphens == 0) {
		return REGULAR_ARGUMENT;
	} else if (leadingHyphens == 1) {
		return SHORT_OPTION;
	} else {
		return LONG_OPTION;
	}
}

