#ifndef _ARGLIB_ARGUMENT_PARSER_H_
#define _ARGLIB_ARGUMENT_PARSER_H_

#include <string>
#include <vector>

class OptionSyntax;
class ArgumentData;

class ArgumentParser {
	public:
		ArgumentParser(OptionSyntax* syntax, ArgumentData* argumentData);

		void parse(int argc, const char* argv[]);
	private:
		int parseShortOption(const std::string& option, const std::vector<std::string>& arguments, int argIndex);
		int parseOption(const std::string& option, const std::vector<std::string>& arguments, int argIndex);
		void saveOption(const std::string& option, const std::string* value);

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
		OptionSyntax* optionSyntax;

		ArgumentData* argData;
};

#endif

