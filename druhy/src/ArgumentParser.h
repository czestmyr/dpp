#ifndef _ARGLIB_ARGUMENT_PARSER_H_
#define _ARGLIB_ARGUMENT_PARSER_H_

#include <string>

class OptionSyntax;

class ArgumentParser {
	public:
		ArgumentParser(OptionSyntax* syntax);

		bool parse(int argc, char* argv[]);
	private:
		enum ArgumentType {
			REGULAR_ARGUMENT,
			SHORT_OPTION,
			LONG_OPTION,
			DOUBLE_HYPHEN_SEPARATOR
		};

		ArgumentType determineType(const std::string& argument);

		/// Tells whether all the remaining arguments should be treated as regular arguments
		bool allRegular;

		/// OptionSyntax object that can be queried on existing options and their properties
		OptionSyntax* mySyntax;
};

#endif

