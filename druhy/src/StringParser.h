#ifndef _ARGLIB_STRING_PARSER_H_
#define _ARGLIB_STRING_PARSER_H_

#include <string>

#define WHITESPACE std::string(" \t\n\r")
#define NUMBERS std::string("0123456789")
#define LOWERCASE_LETTERS std::string("abcdefghijklmnopqrstuvwxyz")
#define UPPERCASE_LETTERS std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
#define LETTERS (LOWERCASE_LETTERS + UPPERCASE_LETTERS)

/// Defines whether the parsing functions in StringMatcher will parse until they
/// find a character outside the given set (NORMAL) or from the given set (INVERSED)
enum CharMatchingLogic {
	NORMAL,
	INVERSED
};

class StringParser {
	public:
		StringParser(const std::string& toParse);

		// TODO: Document that these methods always return number of characters parsed
		int parseMany(const std::string& chars, CharMatchingLogic logic = NORMAL);
		int parseOne(const std::string& chars, CharMatchingLogic logic = NORMAL);
		int parseExact(int howMany, const std::string& chars, CharMatchingLogic logic = NORMAL);

		/// Raises a parsing exception
		void raiseException(const std::string& exceptionMessage);
		bool reachedEnd();

		size_t getPosition();
	private:
		int parseOneInternal(const std::string& chars, CharMatchingLogic logic);
		
		const std::string& parsedString;
		size_t position;
};

#endif
