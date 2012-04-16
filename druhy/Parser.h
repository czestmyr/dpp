#ifndef _ARGLIB_PARSER_H_
#define _ARGLIB_PARSER_H_

#include <string>

#define WHITESPACE " \t\n\r"
#define NUMBERS "0123456789"

class Parser {
	public:
		Parser(const std::string& toParse);
	
		int parseMany(const std::string& chars);
		int parseOne(const std::string& chars);

		std::string getError(const std::string& chars);
		bool reachedEnd();
	private:
		int parseOneInternal(const std::string& chars);
		
		const std::string& parsedString;
		size_t position;
};

#endif
