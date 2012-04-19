#ifndef _ARGLIB_STRING_PARSER_H_
#define _ARGLIB_STRING_PARSER_H_

#include <string>

#define WHITESPACE " \t\n\r"
#define NUMBERS "0123456789"
#define LOWERCASE_LETTERS "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTERS (LOWERCASE_LETTERS + UPPERCASE_LETTERS)

class StringParser {
	public:
		StringParser(const std::string& toParse);

		// TODO: Document that these methods always return number of characters parsed
		int parseMany(const std::string& chars);
		int parseOne(const std::string& chars);
		int parseExact(int howMany, const std::string& chars);

		/// Raises a parsing exception
		void raiseException(const std::string& exceptionMessage);
		bool reachedEnd();

		size_t getPosition();
	private:
		int parseOneInternal(const std::string& chars);
		
		const std::string& parsedString;
		size_t position;
};

#endif
