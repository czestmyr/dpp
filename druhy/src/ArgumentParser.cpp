#include <vector>

#include "ArgumentParser.h"
#include "StringParser.h"
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentException.h"
#include "Value.h"

using namespace std;

namespace Arglib {

ArgumentParser::ArgumentParser(OptionSyntax* syntax, ArgumentData* argumentData):
	allRegular(false), optionSyntax(syntax), argData(argumentData) {}

void ArgumentParser::parse(int argc, const char* argv[]) {
	// Before parsing reset dataStorage to empty state
	argData->resetToEmpty();
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

		// How many arguments the parsing ate up
		int indexIncrement = 1;

		// Perform action depending on the argument type
		switch (argType) {
			case REGULAR_ARGUMENT:
				argData->addArgument(argument);
			break;
			case SHORT_OPTION:
				indexIncrement = parseShortOption(arguments[argIndex].substr(1), arguments, argIndex);
			break;
			case LONG_OPTION:
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

	// Check that all the required options are specified
	const set<unsigned int>& requiredOptions = optionSyntax->getRequiredOptions();
	set<unsigned int>::const_iterator it = requiredOptions.begin();
	while (it != requiredOptions.end()) {
		if (!argData->isOptionSet(*it)) {
			string message = string("A required option was not specified: ") +
				optionSyntax->getOptionName(*it);
			throw ArgumentException(message);
		}
		it++;
	}
}

int ArgumentParser::parseShortOption(const string& option, const vector<string>& arguments, int argIndex) {
	// Incorrect format of short option
	if (option.size() != 1 && option[1] != '=') {
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
		// The attribute can sometimes affect parsing
		ParameterAttribute attrib = optionSyntax->getAttribute(option);
		// There is no next argument to use as a parameter
		if (argIndex + 1 >= arguments.size()) {
			saveOption(option, NULL);
			parsedArguments = 1;
		// If a parameter is required, eat up anything that comes next
		} else if (attrib == PARAM_REQUIRED) {
			saveOption(option, &arguments[argIndex + 1]);
			parsedArguments = 2;
		// Next argument is not a regular argument
		} else if (determineType(arguments[argIndex + 1]) != REGULAR_ARGUMENT) {
			saveOption(option, NULL);
			parsedArguments = 1;
		// Next argument is a regular argument, we could use it as a parameter value
		} else {
			// If parameters are forbidden, don't eat them up
			if (attrib == PARAM_FORBIDDEN) {
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
	// NOTE: We don't need to test whether the parameter was allowed, because
	// exceptions will take care of that in the following function calls.

	ParameterAttribute attrib = optionSyntax->getAttribute(option);

	// If the value is specified and the option forbids it, complain
	if (value != NULL && attrib == PARAM_FORBIDDEN) {
		throw ArgumentException(string("Option ") + option +
			" does not allow parameters, but value " + *value + " was given!");
	}

	// If the value is not specified and the option requires it, complain
	if (value == NULL && attrib == PARAM_REQUIRED) {
		throw ArgumentException(string("Option ") + option + " requires a parameter, but none was given!");
	}

	// Try to cast the value of the option to its type
	if (value != NULL) {
		const Type* type = optionSyntax->getParameterType(option);
		Value* optionValue = type->fromString(*value);
		ValueHandle valueHandle(optionValue);

		// If the value could not be cast from string, throw an exception
		if (valueHandle.isEmpty()) {
			throw ArgumentException(string("Parsing the value ") + *value + " unsuccessful!");
		}

		// Save the option into argument data
		unsigned int id = optionSyntax->getId(option);
		argData->setOption(id, valueHandle);
	} else {
		// Save the option into argument data with a default-constructed invalid Value
		unsigned int id = optionSyntax->getId(option);
		argData->setOption(id, ValueHandle());
	}
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

} // End namespace Arglib

