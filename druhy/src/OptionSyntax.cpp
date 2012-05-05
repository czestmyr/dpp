#include "OptionSyntax.h"
#include "ArgumentException.h"
#include "StringParser.h"

#include <set>
#include <list>

using namespace std;

typedef multimap<unsigned int, string> synonym_map;
typedef pair<synonym_map::const_iterator, synonym_map::const_iterator> const_synonym_range;

OptionSyntax::OptionSyntax(): lastId(0) {}

OptionSyntax::~OptionSyntax() {
	// Delete all the types
	map<unsigned int, Type*>::iterator it = types.begin();
	while (it != types.end()) {
		delete it->second;
		it++;
	}
}

void OptionSyntax::addOption(const string& optionName, ParameterAttribute attrib, Type* paramType, const string& helpString) {
	unsigned int id = getUnusedId();
	ids.insert(pair<string, unsigned int>(optionName, id));
	synonyms.insert(pair<unsigned int, string>(id, optionName));
	attributes.insert(pair<unsigned int, ParameterAttribute>(id, attrib));
	types.insert(pair<unsigned int, Type*>(id, paramType));
	if (!helpString.empty()) {
		helpStrings.insert(pair<unsigned int, string>(id, helpString));
	}
}

void OptionSyntax::addSynonym(const string& original, const string& synonym) {
	unsigned int id = getId(original);
	ids.insert(pair<string, unsigned int>(synonym, id));
	synonyms.insert(pair<unsigned int, string>(id, synonym));
}

ParameterAttribute OptionSyntax::getAttribute(const string& option) const {
	unsigned int id = getId(option);
	return attributes.find(id)->second;
}

const Type* OptionSyntax::getType(const string& option) const {
	unsigned int id = getId(option);
	return types.find(id)->second;
}

void OptionSyntax::writeHelp(ostream& stream) const {
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

			// Print the synonyms
			stream << "\t";
			synonym_map::const_iterator synIt = synonyms.find(id);
			const_synonym_range synRange = synonyms.equal_range(id);
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

			// Get the help string
			map<unsigned int, string>::const_iterator helpIt;
			helpIt = helpStrings.find(id);
			string helpString;
			if (helpIt == helpStrings.end()) {
				helpString = "Help for this option not available";
			} else {
				helpString = helpIt->second;
			}

			// Divide the help string into words
			StringParser parser(helpString);
			parser.parseMany(WHITESPACE);
			size_t wordBegin = parser.getPosition();
			size_t wordLen = parser.parseMany(WHITESPACE, INVERSED);
			list<string> words;
			while (wordLen != 0) {
				words.push_back(helpString.substr(wordBegin, wordLen));

				parser.parseMany(WHITESPACE);
				wordBegin = parser.getPosition();
				wordLen = parser.parseMany(WHITESPACE, INVERSED);
			}

			//TODO: Add terminal width as a user-defined parameter
			int terminalWidth = 80;
			int availableSize = terminalWidth - 16;
			int wordsLength = 0;
			int wordNum = 0;
			list<string>::iterator wordIt = words.begin();
			list<string>::iterator lineBegin = wordIt;
			while (wordIt != words.end()) {
				// If the next word would overflow the line, don't add it.
				if (wordsLength + wordIt->length() + (wordNum-1) > availableSize && wordNum != 0) {
					list<string>::iterator it = lineBegin;
					stream << "\t\t";
					while (it != wordIt) {
						if (it != lineBegin) {
							stream << " ";
						}
						stream << *it;
						it++;
					}
					stream << endl;

					lineBegin = wordIt;
					wordsLength = 0;
					wordNum = 0;
				}

				wordsLength += wordIt->length();
				wordNum++;
				wordIt++;
			}
			// Print the last remaining line
			list<string>::iterator it = lineBegin;
			stream << "\t\t";
			while (it != wordIt) {
				if (it != lineBegin) {
					stream << " ";
				}
				stream << *it;
				it++;
			}

			stream << endl;
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

