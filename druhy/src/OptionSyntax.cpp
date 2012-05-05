#include "OptionSyntax.h"
#include "ArgumentException.h"
#include "StringParser.h"

#include <set>

using namespace std;

typedef multimap<unsigned int, string> SynonymMap;
typedef pair<SynonymMap::const_iterator, SynonymMap::const_iterator> ConstSynonymRange;

OptionSyntax::OptionSyntax(): lastId(0) {}

OptionSyntax::~OptionSyntax() {
	// Delete all the types
	map<unsigned int, Type*>::iterator it = types.begin();
	while (it != types.end()) {
		delete it->second;
		it++;
	}
}

void OptionSyntax::addOption(const string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib) {
	unsigned int id = getUnusedId();
	ids.insert(pair<string, unsigned int>(optionName, id));
	synonyms.insert(pair<unsigned int, string>(id, optionName));
	optionAttributes.insert(pair<unsigned int, OptionAttribute>(id, optionAttrib));
	paramAttributes.insert(pair<unsigned int, ParameterAttribute>(id, paramAttrib));
	types.insert(pair<unsigned int, Type*>(id, paramType));
}

void OptionSyntax::addSynonym(const string& original, const string& synonym) {
	unsigned int id = getId(original);
	ids.insert(pair<string, unsigned int>(synonym, id));
	synonyms.insert(pair<unsigned int, string>(id, synonym));
}

ParameterAttribute OptionSyntax::getAttribute(const string& option) const {
	unsigned int id = getId(option);
	return paramAttributes.find(id)->second;
}

const Type* OptionSyntax::getType(const string& option) const {
	unsigned int id = getId(option);
	return types.find(id)->second;
}

void OptionSyntax::setOptionHelp(const string& option, const string& helpString) {
	unsigned int id = getId(option);
	helpStrings.insert(pair<unsigned int, string>(id, helpString));
}

void OptionSyntax::writeHelp(ostream& stream, int terminalSize) const {
	stream << "\tOption help:" << endl << endl;

	// We iterate over all option ids until we encounter a new one
	set<unsigned int> processedIds;
	map<string, unsigned int>::const_iterator idIt = ids.begin();
	while (idIt != ids.end()) {
		unsigned int id = idIt->second;

		// A new option id has been found - print its synonymous option strings
		// and append the help string
		if (processedIds.count(id) == 0) {
			processedIds.insert(id);

			writeSynonyms(id, stream);

			// Get the help string
			map<unsigned int, string>::const_iterator helpIt;
			helpIt = helpStrings.find(id);
			string helpString;
			if (helpIt == helpStrings.end()) {
				helpString = "Help for this option not available";
			} else {
				helpString = helpIt->second;
			}

			writeWithLimit(helpString, terminalSize, stream);
		}

		idIt++;
	}
}

unsigned int OptionSyntax::getId(const string& option) const {
	if (ids.count(option) == 0) {
		throw ArgumentException("Unknown option: " + option);
	}

	// Find will not fail here, because we tested presence of the option in ID map
	return ids.find(option)->second;
}

unsigned int OptionSyntax::getUnusedId() {
	lastId++;
	return lastId;
}

void OptionSyntax::writeSynonyms(unsigned int id, ostream& stream) const {
	stream << "\t";

	// Find the range of synonyms in the synonym multimap
	SynonymMap::const_iterator synIt = synonyms.find(id);
	ConstSynonymRange synRange = synonyms.equal_range(id);

	// Write out the list of the synonyms, prepended with dashes and divided by commas
	for (synIt = synRange.first; synIt != synRange.second; synIt++) {
		if (synIt != synRange.first) {
			stream << ", ";
		}
		// Print the correct number of dashes according to length of synonym
		if (synIt->second.size() == 1) {
			stream << "-";
		} else {
			stream << "--";
		}
		stream << synIt->second;
	}
	stream << endl;
}

void OptionSyntax::writeWithLimit(string& str, int limit, ostream& stream) const {
	list<string> words;

	// Divide the string into words
	StringParser parser(str);
	parser.parseMany(WHITESPACE);
	size_t wordBegin = parser.getPosition();
	size_t wordLen = parser.parseMany(WHITESPACE, INVERSED);
	while (wordLen != 0) {
		words.push_back(str.substr(wordBegin, wordLen));
		parser.parseMany(WHITESPACE);
		wordBegin = parser.getPosition();
		wordLen = parser.parseMany(WHITESPACE, INVERSED);
	}

	// Write out the words until they fit into available space
	int availableSize = limit - 16;
	int wordsLength = 0;
	int wordNum = 0;
	list<string>::iterator wordIt = words.begin();
	list<string>::iterator lineBegin = wordIt;
	while (wordIt != words.end()) {
		// If the next word would overflow the line, don't add it, but write out the line
		// Don't write out the line if there are no words to write out
		if (wordsLength + wordIt->length() + (wordNum-1) > availableSize && wordNum != 0) {
			writeOutLine(lineBegin, wordIt, stream);

			// Reset the counters and iterators
			lineBegin = wordIt;
			wordsLength = 0;
			wordNum = 0;
		}

		wordsLength += wordIt->length();
		wordNum++;
		wordIt++;
	}

	// Print the last remaining line
	writeOutLine(lineBegin, wordIt, stream);
}

void OptionSyntax::writeOutLine(StrListIt lineBegin, StrListIt lineEnd, ostream& stream) const {
	list<string>::iterator it = lineBegin;
	stream << "\t\t";
	while (it != lineEnd) {
		if (it != lineBegin) {
			stream << " ";
		}
		stream << *it;
		it++;
	}
	stream << endl;
}

