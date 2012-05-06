#include <cstdlib>
#include "EnumType.h"
#include "../values/Values.h"
#include "../StringParser.h"

using namespace std;

EnumType::EnumType() {
	parameterName = "ENUM";
}

void EnumType::addAllowedStrings(const std::vector<std::string>& newStrings) {
	allowedStrings.insert(newStrings.begin(),newStrings.end());
}

void EnumType::addAllowedString(const std::string& newString) {
	allowedStrings.insert(newString);
}
Value* EnumType::fromString(const string& argument) const {

	StringParser argParser(argument);
	
	argParser.parseMany(WHITESPACE);  //WHITESPACE constant in parser function header

	// Fail if no word could be parsed
	size_t wordBegin = argParser.getPosition();
	if (argParser.parseMany(WORD_LETTERS) == 0) {
		argParser.raiseException("No word addded as parameter");
	}
	size_t wordEnd = argParser.getPosition();
	argParser.parseMany(WHITESPACE);
	
	// Fail if there are any trailing characters
	if (!argParser.reachedEnd()) {
		argParser.raiseException("Parameter containst more words with whitespaces inbetween");
	}
	// Exacts the word from argument
	string cleanedArgument = argument.substr(wordBegin, wordEnd);

	set<string>::iterator it = allowedStrings.find(cleanedArgument);
	if (it == allowedStrings.end()){
		argParser.raiseException("Argument value: " + cleanedArgument + " isn't allowed in this option");
	}
	// Set and return the correct value
	StringValue* val = new StringValue(cleanedArgument);
	return val;
}

Type* EnumType::clone() const {
	return new EnumType(*this);
}

