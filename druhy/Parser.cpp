#include "Parser.h"

using namespace std;

Parser::Parser(const string& toParse): parsedString(toParse), position(0) {}

int Parser::parseMany(const string& chars) {
	int parsedChars = 0;
  
	// Repeatedly try to parse one character and return the number of successes
	while (parseOneInternal(chars)) {
		parsedChars++;
	}

	return parsedChars;
}

int Parser::parseOne(const string& chars) {
	return parseOneInternal(chars);
}

string Parser::getError(const std::string& chars) {
	return "";  // TODO
}

bool Parser::reachedEnd() {
	return position == parsedString.length();
}

int Parser::parseOneInternal(const string& chars) {
	for (int i = 0; i < chars.length(); ++i) {
	  if (!reachedEnd() && parsedString[position] == chars[i]) {
			position++;
			return 1;
		}
	}
	
	return 0;
}

