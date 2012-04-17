#ifndef _ARGLIB_ARGUMENT_PARSER_H_
#define _ARGLIB_ARGUMENT_PARSER_H_

#include <string>

class ArgumentParser {
	public:
		ArgumentParser();

		bool parse(int argc, char* argv[]);
	private:
		enum ArgumentType {
			REGULAR_ARGUMENT,
			SHORT_OPTION,
			LONG_OPTION
		};

		ArgumentType determineType(const std::string& argument);

		/// Tells whether all the remaining arguments should be treated as regular arguments
		bool allRegular;
};

#endif

