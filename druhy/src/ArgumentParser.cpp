#include <vector>

#include "ArgumentParser.h"
#include "StringParser.h"
#include "OptionSyntax.h"

// TODO: Remove this before handing in
#include <iostream>

using namespace std;

ArgumentParser::ArgumentParser(OptionSyntax* syntax): allRegular(false), mySyntax(syntax) {}

bool ArgumentParser::parse(int argc, char* argv[]) {
	// Convert arguments to std::strings for better manipulation
	vector<string> arguments;
	for (int i = 1; i < argc; ++i) {  // The zeroth argument is the name of the executable
		arguments.push_back(string(argv[i]));
	}

	// Parse the arguments
	int argIndex = 0;
	while (argIndex < arguments.size()) {
		string& argument = arguments[argIndex];
		ArgumentType argType = determineType(argument);

		int indexIncrement = 1;
		switch (argType) {
			case REGULAR_ARGUMENT:
				// Save the argument somewhere together with it's information
				std::cout << argument << " is a regular argument." << std::endl;
				// TODO: Implement the argument saving
			break;
			case SHORT_OPTION:
				// Parse the short option
				std::cout << argument << " is a short option." << std::endl;
				indexIncrement = parseShortOption(arguments[argIndex].substr(1), arguments, argIndex);
			break;
			case LONG_OPTION:
				// Parse the long option
				std::cout << argument << " is a long option." << std::endl;
				indexIncrement = parseOption(arguments[argIndex].substr(2), arguments, argIndex);
			break;
			case DOUBLE_HYPHEN_SEPARATOR:
				// Make all further arguments regular
				allRegular = true;
			break;
			default:
				// This shouldn't happen
				return false;
		}

		// Parsing functions denote a failure by returning zero
		if (indexIncrement == 0) {
			return false;
		}

		argIndex += indexIncrement;
	}

	// If we got here, the arguments were parsed successfully.
	return true;
}

int ArgumentParser::parseShortOption(const string& option, const vector<string>& arguments, int argIndex) {
	// Incorrect format of short option
	if (option.size() != 1) {		
		cout << "Short option has incorrect format!" << endl;
		return 0;  // TODO: Print some error information in a proper way!
	}

	// Short options are just a special case of regular options
	parseOption(option, arguments, argIndex);
}

int ArgumentParser::parseOption(const string& option, const vector<string>& arguments, int argIndex) {
	cout << "Option would be parsed now!" << endl;  // TODO: This is just a test. DO some proper logging in future!
	cout << "Option name: " << option << endl;

	return 1;
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
	} else if (leadingHyphens == 2 && parser.reachedEnd()) {
		return DOUBLE_HYPHEN_SEPARATOR;
	} else {
		return LONG_OPTION;
	}
}

