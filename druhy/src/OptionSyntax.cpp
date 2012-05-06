#include "OptionSyntax.h"
#include "ArgumentException.h"
#include "StringParser.h"

#include <set>

using namespace std;

typedef multimap<unsigned int, string> SynonymMap;
typedef pair<SynonymMap::const_iterator, SynonymMap::const_iterator> ConstSynonymRange;
typedef map<unsigned int, ParameterAttribute> ParamAttributeMap;
typedef map<unsigned int, Type*> ParamTypeMap;

OptionSyntax::OptionSyntax(): lastId(0) {}

OptionSyntax::OptionSyntax(const OptionSyntax& other) {
	initFrom(other);
}

OptionSyntax::~OptionSyntax() {
	deinit();
}

OptionSyntax& OptionSyntax::operator=(const OptionSyntax& other) {
	deinit();
	initFrom(other);
}

void OptionSyntax::addOption(const string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib) {
	if(isOptionDefined(optionName)) {
		// Prevent type memory leaking by deleting the newly copied type
		delete paramType;
		throw ArgumentException("Option: " + optionName + "has been already defined");
	}
	unsigned int id = getUnusedId();
	ids.insert(pair<string, unsigned int>(optionName, id));
	synonyms.insert(pair<unsigned int, string>(id, optionName));
	paramAttributes.insert(pair<unsigned int, ParameterAttribute>(id, paramAttrib));
	types.insert(pair<unsigned int, Type*>(id, paramType));


	if (optionAttrib == OPTION_REQUIRED) {
		requiredOptions.insert(id);
	}
}

void OptionSyntax::addSynonym(const string& original, const string& synonym) {
	if(isOptionDefined(synonym)) {
		throw ArgumentException("Option: " + synonym + "has been already defined");
	}
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
	stream << "\tOption help:" << endl;
	stream << "\t(* = Required option; [ PARAM ] = Optional parameter)" << endl << endl;

	// We iterate over all option ids until we encounter a new one
	set<unsigned int> processedIds;
	map<string, unsigned int>::const_iterator idIt = ids.begin();
	while (idIt != ids.end()) {
		unsigned int id = idIt->second;

		// A new option id has been found - print its synonymous option strings
		// and append the help string
		if (processedIds.count(id) == 0) {
			processedIds.insert(id);

			stream << "\t";
			// Write out option attribute if necessarry
			if (requiredOptions.count(id) > 0) {
				stream << "*";
			}
			writeSynonyms(id, stream);
			writeParameter(id, stream);
			
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

const set<unsigned int>& OptionSyntax::getRequiredOptions() const {
	return requiredOptions;
}

void OptionSyntax::deinit() {
	// Delete all the types
	ParamTypeMap::iterator it = types.begin();
	while (it != types.end()) {
		delete it->second;
		it++;
	}
}

void OptionSyntax::initFrom(const OptionSyntax& other) {
	lastId = other.lastId;
	ids = other.ids;
	synonyms = other.synonyms;
	paramAttributes = other.paramAttributes;
	helpStrings = other.helpStrings;
	requiredOptions = other.requiredOptions;

	// Clone all the types from the other syntax
	types.clear();
	ParamTypeMap::const_iterator it = other.types.begin();
	while (it != other.types.end()) {
		types.insert(pair<unsigned int, Type*>(it->first, it->second->clone()));
		it++;
	}
}

unsigned int OptionSyntax::getUnusedId() {
	lastId++;
	return lastId;
}

bool OptionSyntax::isOptionDefined(const string& optionName) const {
	return (ids.find(optionName) != ids.end());
}

void OptionSyntax::writeSynonyms(unsigned int id, ostream& stream) const {
	stream << " ";

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
}

void OptionSyntax::writeParameter(unsigned int id, std::ostream& stream) const {
	// Find out whether there is any parameter at all and what is its attribute
	ParamAttributeMap::const_iterator attrIt = paramAttributes.find(id);
	if (attrIt == paramAttributes.end()) {
		return;
	}

	ParameterAttribute attrib = attrIt->second;
	if (attrib == PARAM_FORBIDDEN) {
		return;
	}

	ParamTypeMap::const_iterator typeIt = types.find(id);
	if (typeIt == types.end()) {
		return;
	}

	stream << " ";

	// Write out the parameter with brackets if it is optional.
	if (attrib == PARAM_ALLOWED) {
		stream << "[ ";
	}
	Type* paramType = typeIt->second;
	stream << paramType->syntaxHelpPlaceholder();
	if (attrib == PARAM_ALLOWED) {
		stream << " ]";
	}
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

