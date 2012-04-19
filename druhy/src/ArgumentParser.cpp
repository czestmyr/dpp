#include <vector>

#include "ArgumentParser.h"
#include "StringParser.h"
#include "OptionSyntax.h"
#include "ArgumentList.h"
#include "ArgumentException.h"
#include "Value.h"

// TODO: Remove this before handing in
#include <iostream>

using namespace std;

ArgumentParser::ArgumentParser(OptionSyntax* syntax, ArgumentList* argumentList):
	allRegular(false), optionSyntax(syntax), argList(argumentList) {}

void ArgumentParser::parse(int argc, char* argv[]) {
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
				argList->addArgument(argument);
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
				throw ArgumentException("Internal error in the Arglib library");
		}
		argIndex += indexIncrement;
	}
}

int ArgumentParser::parseShortOption(const string& option, const vector<string>& arguments, int argIndex) {
	// Incorrect format of short option
	if (option.size() != 1) {
		throw ArgumentException("Short option has incorrect format");
	}

	// Short options are just a special case of longer options
	parseOption(option, arguments, argIndex);
}

int ArgumentParser::parseOption(const string& option, const vector<string>& arguments, int argIndex) {
	// Get the option name and parameter value and save them
	size_t equalSignPos = option.find("=");
	int parsedArguments = 1;
	if (equalSignPos == string::npos) {
		// There is no next argument to use as a parameter
		if (argIndex + 1 >= arguments.size()) {
			saveOption(option, NULL);
			parsedArguments = 1;
		// Next argument is not a regular argument
		} else if (determineType(arguments[argIndex + 1]) != REGULAR_ARGUMENT) {
			saveOption(option, NULL);
			parsedArguments = 1;
		// Next argument is a regular argument, we could use it as a parameter value
		} else {
			// The syntax has to be queried here prematurely to prevent fail
			ParameterAttribute attrib = optionSyntax->getAttribute(option);
			// If parameters are forbidden, don't eat them up
			if (attrib == FORBIDDEN) {
				saveOption(option, NULL);
				parsedArguments = 1;
			} else {
				saveOption(option, &arguments[argIndex + 1]);
				parsedArguments = 2;
			}
		}
	} else {
		// Value for the option is in the option string
		string optionName = option.substr(0, equalSignPos);
		string parameterValue = option.substr(equalSignPos + 1, string::npos);
		saveOption(optionName, &parameterValue);
		parsedArguments = 1;
	}

	return parsedArguments;
}

void ArgumentParser::saveOption(const std::string& option, const std::string* value) {
	if (value != NULL)
		cout << "Saving option value: \"" << option << "\"=\"" << *value << "\"" << endl;
	else
		cout << "Saving option value: \"" << option << "\"=NULL" << endl;

	// NOTE: We don't need to test whether the option was allowed, because
	// exceptions will take care of that in the following function calls.

	ParameterAttribute attrib = optionSyntax->getAttribute(option);

	// If the value is specified and the option forbids it, complain
	if (value != NULL && attrib == FORBIDDEN) {
		throw ArgumentException(string("Option ") + option + " does not allow parameters, but value " + value + " was given!");
	}

	// If the value is not specified and the option requires it, complain
	if (value == NULL && attrib == REQUIRED) {
		throw ArgumentException(string("Option ") + option + " requires a parameter, but none was given!");
	}

	// Try to cast the value of the option to its type
	IType* type = optionSyntax->getType(option);
	if (type == NULL) {
		throw ArgumentException(string("Type for option ") + option + " was not specified");
	}
	Value castValue = type->fromString(*value);

	// If the value could not be cast from string, throw an exception
	if (!castValue.valid()) {
		throw ArgumentException(string("Parsing the value ") + value + " unsuccessful!");
	}

	// TODO: Save the value somewhere
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

