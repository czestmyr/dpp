#include "OptionSyntax.h"
#include "ArgumentException.h"

#include <set>
#include <sstream>

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

			// Print the help string
			map<unsigned int, string>::const_iterator helpIt;
			helpIt = helpStrings.find(id);
			if (helpIt == helpStrings.end()) {
				stream << "\t\t" << "Help for this option not available";
			} else {
				stream << "\t\t" << helpIt->second;
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

