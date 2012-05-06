#ifndef _ARGLIB_ARGUMENT_PARSER_H_
#define _ARGLIB_ARGUMENT_PARSER_H_

#include <string>
#include <vector>

namespace Arglib {

class OptionSyntax;
class ArgumentData;

/// Parses command-line options and uses OptionSyntax and ArgumentData to further process the parsed data.
/// Option syntax confirmity is checked by asking the OptionSyntax object and the data is then set using the
/// ArgumentData object.
class ArgumentParser {
	public:
		/// Initializes the argument parser.
		/// The parser gets only pointers to the OptionSyntax and ArgumentData objects so that it can work
		/// with them.
		/// @param syntax Pointer to the syntax object that stores information about defined options.
		/// @param argumentData Pointer to the object where the options will be stored.
		ArgumentParser(OptionSyntax* syntax, ArgumentData* argumentData);

		/// Parses the command-line arguments
		/// @param argc as in standard C++ main function.
		/// @param argv as in standard C++ main function.
		/// @throws ArgumentException In case the parsing can't be finished due to error.
		void parse(int argc, const char* argv[]);
	private:
		/// Internal helper method for short option parsing.
		/// It does some short-option specific things and then calls the normal option internal parsing method.
		/// @param option Name of the parsed option (should be actually only one character)
		/// @param arguments reference to the internal vector of parsed arguments
		/// @param argIndex The index that corresponds to the currently parsed option
		/// @throws ArgumentException If the short option has incorect format.
		int parseShortOption(const std::string& option, const std::vector<std::string>& arguments, int argIndex);

		/// Internal helper method for option parsing.
		/// Does some parsing and tries to save the option value.
		/// @param option Name of the parsed option (should be actually only one character)
		/// @param arguments reference to the internal vector of parsed arguments
		/// @param argIndex The index that corresponds to the currently parsed option
		/// @throws ArgumentException If the option can't be saved.
		int parseOption(const std::string& option, const std::vector<std::string>& arguments, int argIndex);

		/// Saves the value of the option parameter into the ArgumentData object.
		/// @param option The option whose parameter's value is being set
		/// @param value pointer to the string that represents the parameter's value.
		/// @throws ArgumentException If the option can't be saved.
		void saveOption(const std::string& option, const std::string* value);

		/// Enum that defines all possible argument types
		enum ArgumentType {
			REGULAR_ARGUMENT,       ///< Argument that could visually be neither an option, or a separator
			SHORT_OPTION,           ///< A short option argument
			LONG_OPTION,            ///< A long option argument
			DOUBLE_HYPHEN_SEPARATOR ///< A separator of options and regular arguments
		};

		/// Determines type of the given argument.
		/// @param argument the argment whose type is to be determined.
		/// @return type of the argument, as it appears visually (i.e. without context of other arguments)
		ArgumentType determineType(const std::string& argument);

		/// Tells whether all the remaining arguments should be treated as regular arguments
		bool allRegular;

		/// OptionSyntax object that can be queried on existing options and their properties
		OptionSyntax* optionSyntax;

		/// ArgumentData object that is used to save the options and their parameters
		ArgumentData* argData;
};

} // End namespace Arglib

#endif

