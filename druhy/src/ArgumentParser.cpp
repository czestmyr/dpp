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
	for (int i = 1; i < argc; ++i) {
		arguments.push_back(argv[i]);
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

	// Short options are just a special case of longer options
	parseOption(option, arguments, argIndex);
}

int ArgumentParser::parseOption(const string& option, const vector<string>& arguments, int argIndex) {
	cout << "Option would be parsed now!" << endl;  // TODO: This is just a test. Do some proper logging in future!
	cout << "Option name: " << option << endl;

	// Get the option name and parameter value and save them
	size_t equalSignPos = option.find("=");
	int parsedArguments = 1;
	bool success = false;
	if (equalSignPos == string::npos) {
		// There is no next argument to use as a parameter
		if (argIndex + 1 >= arguments.size()) {
			success = saveOption(option, NULL);
			parsedArguments = 1;
		// Next argument is not a regular argument
		} else if (determineType(arguments[argIndex + 1]) != REGULAR_ARGUMENT) {
			success = saveOption(option, NULL);
			parsedArguments = 1;
		// Next argument is a regular argument, we could use it as a parameter value
		} else {
			ParameterAttribute attrib = mySyntax->getAttribute(option);
			// If parameters are forbidden, don't eat them up
			if (attrib == FORBIDDEN || attrib == INVALID) {
				success = saveOption(option, NULL);
				parsedArguments = 1;
			} else {
				success = saveOption(option, &arguments[argIndex + 1]);
				parsedArguments = 2;
			}
		}
	} else {
		// Value for the option is in the option string
		string optionName = option.substr(0, equalSignPos);
		string parameterValue = option.substr(equalSignPos + 1, string::npos);
		success = saveOption(optionName, &parameterValue);
		parsedArguments = 1;
	}

	if (!success) {
		return 0;
	} else {
		return parsedArguments;
	}
}

bool ArgumentParser::saveOption(const std::string& option, const std::string* value) {
	if (value != NULL)
		cout << "Saving option value: \"" << option << "\"=\"" << *value << "\"" << endl;
	else
		cout << "Saving option value: \"" << option << "\"=NULL" << endl;
	return true;
	// TODO: Implement this
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

