#include "StringParser.h"

using namespace std;

StringParser::StringParser(const string& toParse): parsedString(toParse), position(0) {}

int StringParser::parseMany(const string& chars) {
	int parsedChars = 0;
  
	// Repeatedly try to parse one character and return the number of successes
	while (parseOneInternal(chars)) {
		parsedChars++;
	}

	return parsedChars;
}

int StringParser::parseOne(const string& chars) {
	return parseOneInternal(chars);
}

int StringParser::parseExact(int howMany, const std::string& chars) {
	int parsedChars = 0;

	// Repeatedly try to parse one character and return the number of successes
	while (parseOneInternal(chars) && parsedChars < howMany) {
		parsedChars++;
	}

	return parsedChars;
}

string StringParser::getError(const std::string& chars) {
	return "";  // TODO
}

bool StringParser::reachedEnd() {
	return position == parsedString.length();
}

int StringParser::parseOneInternal(const string& chars) {
	// If there is nothing to parse, return
	if (reachedEnd()) {
		return 0;
	}

	for (int i = 0; i < chars.length(); ++i) {
		if (parsedString[position] == chars[i]) {
			position++;
			return 1;
		}
	}
	
	return 0;
}
