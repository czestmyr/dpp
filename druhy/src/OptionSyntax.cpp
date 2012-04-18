#include "OptionSyntax.h"

using namespace std;

OptionSyntax::OptionSyntax(): lastId(0) {}

void OptionSyntax::addOption(const std::string& optionName, ParameterAttribute attrib, IType* type) {
	unsigned int id = getUnusedId();
	ids.insert(pair<std::string, unsigned int>(optionName, id));
	attributes.insert(pair<unsigned int, ParameterAttribute>(id, attrib));
	types.insert(pair<unsigned int, IType*>(id, type));
	helpStrings.insert(pair<unsigned int, std::string>(id, ""));
}

bool OptionSyntax::setSynonymous(const std::string& option1, const std::string& option2) {
	// TODO: implement
}

bool OptionSyntax::setOptionHelp(const std::string& optionName, const std::string& helpString) {
	// TODO: implement
}

bool OptionSyntax::wasAdded(const std::string& option) const {
	return ids.count(option) != 0;
}

ParameterAttribute OptionSyntax::getAttribute(const std::string& option) const {
	if (ids.count(option) == 0) {
		return INVALID;
	}

	// Find will not fail here, because we tested presence of the option
	// in ID map and attributes will always have an entry for existing id
	unsigned int id = (*ids.find(option)).second;
	return (*attributes.find(id)).second;
}

const IType* OptionSyntax::getType(const std::string& option) const {
	if (ids.count(option) == 0) {
		return NULL;
	}

	// Find will not fail here, because we tested presence of the option
	// in ID map and types will always have an entry for existing id
	unsigned int id = (*ids.find(option)).second;
	return (*types.find(id)).second;
}

const std::string& OptionSyntax::getHelp(const std::string& option) const {
	if (ids.count(option) == 0) {
		return emptyHelp;
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

string OptionSyntax::emptyHelp = "";

