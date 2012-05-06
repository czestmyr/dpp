#ifndef _ARGLIB_STRING_PARSER_H_
#define _ARGLIB_STRING_PARSER_H_

#include <string>

/// A set of whitespace characters
#define WHITESPACE std::string(" \t\n\r")
/// A set of numbers
#define NUMBERS std::string("0123456789")
/// A set of lowercase letters
#define LOWERCASE_LETTERS std::string("abcdefghijklmnopqrstuvwxyz")
/// A set of uppercase letters
#define UPPERCASE_LETTERS std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
/// A set of letters
#define LETTERS (LOWERCASE_LETTERS + UPPERCASE_LETTERS)
/// A set of delimiters that can be inside a word in enums
#define WORD_DELIMITERS std::string("_-")
/// A set of letters that can be inside a word in enums
#define WORD_LETTERS (LETTERS + WORD_DELIMITERS)

/// Character matching logic for the StringParser.
/// Defines whether the parsing functions in StringMatcher will parse until they
/// find a character outside the given set (NORMAL) or from the given set (INVERSED)
enum CharMatchingLogic {
	NORMAL, ///< Normal matching logic - parse until you find a character that does not match the given set.
	INVERSED ///< Inversed matching logic - parse until you find a character from the given set.
};

/// Simplifies parsing strings by stepping over characters from or outside of a given set.
/// The parsing is done by specifying the sets of characters which we want to see in the string and the parser steps
/// over the characters, reporting the number of characters parsed. While parsing, the parser increments the current
/// position.
/// 
/// The parser is initialized by giving it a reference to the string that will be parsed. During the parsing of the
/// string, the string should not be modified or the parser might not work properly.
class StringParser {
	public:
		/// Initializes the parser and resets the internal position to the beginning of the string.
		/// @param toParse the string to be parsed.
		StringParser(const std::string& toParse);

		/// Parses zero to (theoretically) infinitely many matching the given definition. The characters have
		/// to be either from or outside the given set. This is specified by the logic parameter. If the
		/// parser reaches the end of the parsed string, calls to this method will always return zero.
		/// @param chars The set of characters we match against.
		/// @param logic Whether to match against the set given by chars or against its complement.
		/// @return number of characters parsed.
		int parseMany(const std::string& chars, CharMatchingLogic logic = NORMAL);

		/// Parses either zero or one character that matches the given definition. The character has
		/// to be either from or outside the given set. This is specified by the logic parameter. If the
		/// parser reaches the end of the parsed string, calls to this method will always return zero.
		/// @param chars The set of characters we match against.
		/// @param logic Whether to match against the set given by chars or against its complement.
		/// @return number of characters parsed - i.e. either one or zero.
		int parseOne(const std::string& chars, CharMatchingLogic logic = NORMAL);

		/// Parses zero to howMany characters matching the given definition. If not enough characters match
		/// the given definition, as many characters as possible are eaten up and their number is returned.
		/// The characters have to be either from or outside the given set. This is specified by the logic
		/// parameter. If the parser reaches the end of the parsed string, calls to this method will always
		/// return zero.
		/// @param howMany Maximum number of characters to match.
		/// @param chars The set of characters we match against.
		/// @param logic Whether to match against the set given by chars or against its complement.
		/// @return number of characters parsed.
		int parseExact(int howMany, const std::string& chars, CharMatchingLogic logic = NORMAL);

		/// Raises a parsing exception.
		/// This method has to be used to inform the user of Arglib about a parsing exception.
		/// @param exceptionMessage the message that will be shown by calling the exception's method what()
		void raiseException(const std::string& exceptionMessage);

		/// Whether the parser reached end of the string.
		/// @return true when the parser reached end of the string.
		bool reachedEnd();

		/// Returns the current position of the internal position counter.
		/// @return current position of the parser in the string.
		size_t getPosition();
	private:
		/// Internal parsing function used by public parsing functions.
		/// @param chars The set of characters we match against.
		/// @param logic Whether to match against the set given by chars or against its complement.
		/// @return number of characters parsed - i.e. either one or zero.
		int parseOneInternal(const std::string& chars, CharMatchingLogic logic);
		
		const std::string& parsedString; ///< Reference to the parsed string.
		size_t position; ///< Internal position counter.
};

#endif
