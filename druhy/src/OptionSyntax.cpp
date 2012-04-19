#include "OptionSyntax.h"
#include "ArgumentException.h"

using namespace std;

OptionSyntax::OptionSyntax(): lastId(0) {}

void OptionSyntax::addOption(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const string& helpString) {
	unsigned int id = getUnusedId();
	ids.insert(pair<std::string, unsigned int>(optionName, id));
	attributes.insert(pair<unsigned int, ParameterAttribute>(id, attrib));
	types.insert(pair<unsigned int, IType*>(id, paramType));
	helpStrings.insert(pair<unsigned int, std::string>(id, helpString));
}

void OptionSyntax::addSynonym(const std::string& original, const std::string& synonym) {
	// TODO: implement
}

ParameterAttribute OptionSyntax::getAttribute(const std::string& option) const {
	if (ids.count(option) == 0) {
		throw ArgumentException("Unknown option: " + option);
	}

	// Find will not fail here, because we tested presence of the option
	// in ID map and attributes will always have an entry for existing id
	unsigned int id = (*ids.find(option)).second;
	return (*attributes.find(id)).second;
}

const IType* OptionSyntax::getType(const std::string& option) const {
	if (ids.count(option) == 0) {
		throw ArgumentException("Unknown option: " + option);
	}

	// Find will not fail here, because we tested presence of the option
	// in ID map and types will always have an entry for existing id
	unsigned int id = (*ids.find(option)).second;
	return (*types.find(id)).second;
}

const std::string& OptionSyntax::getHelp(const std::string& option) const {
	if (ids.count(option) == 0) {
		throw ArgumentException("Unknown option: " + option);
	}

	// Find will not fail here, because we tested presence of the option
	// in ID map and helpStrings will always have an entry for existing id
	unsigned int id = (*ids.find(option)).second;
	return (*helpStrings.find(id)).second;
}

unsigned int OptionSyntax::getUnusedId() {
	lastId++;
	return lastId;
}

