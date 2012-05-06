#include "StringParser.h"
#include "ArgumentException.h"

using namespace std;

namespace Arglib {

StringParser::StringParser(const string& toParse): parsedString(toParse), position(0) {}

int StringParser::parseMany(const string& chars, CharMatchingLogic logic) {
	int parsedChars = 0;
  
	// Repeatedly try to parse one character and return the number of successes
	while (parseOneInternal(chars, logic)) {
		parsedChars++;
	}

	return parsedChars;
}

int StringParser::parseOne(const string& chars, CharMatchingLogic logic) {
	return parseOneInternal(chars, logic);
}

int StringParser::parseExact(int howMany, const std::string& chars, CharMatchingLogic logic) {
	int parsedChars = 0;

	// Repeatedly try to parse one character and return the number of successes
	while (parseOneInternal(chars, logic) && parsedChars < howMany) {
		parsedChars++;
	}

	return parsedChars;
}

void StringParser::raiseException(const std::string& exceptionMessage) {
	throw ArgumentException(exceptionMessage);
}

bool StringParser::reachedEnd() {
	return position == parsedString.length();
}

size_t StringParser::getPosition() {
	return position;
}

int StringParser::parseOneInternal(const string& chars, CharMatchingLogic logic) {
	// If there is nothing to parse, return
	if (reachedEnd()) {
		return 0;
	}

	for (int i = 0; i < chars.length(); ++i) {
		if (parsedString[position] == chars[i]) {
			if (logic == NORMAL) {
				position++;
				return 1;
			} else {  // logic = INVERSED
				return 0;
			}
		}
	}

	if (logic == NORMAL) {	
		return 0;
	} else {  // logic = INVERSED
		position++;
		return 1;
	}
}

} // End namespace Arglib

