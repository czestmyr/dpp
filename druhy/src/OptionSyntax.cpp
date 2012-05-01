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
	unsigned int id = getId(original);
	ids.insert(pair<std::string, unsigned int>(synonym, id));
}

ParameterAttribute OptionSyntax::getAttribute(const std::string& option) const {
	unsigned int id = getId(option);
	return (*attributes.find(id)).second;
}

const IType* OptionSyntax::getType(const std::string& option) const {
	unsigned int id = getId(option);
	return (*types.find(id)).second;
}

const std::string& OptionSyntax::getHelp(const std::string& option) const {
	unsigned int id = getId(option);
	return (*helpStrings.find(id)).second;
}

unsigned int OptionSyntax::getId(const std::string& option) const {
	if (ids.count(option) == 0) {
		throw ArgumentException("Unknown option: " + option);
	}

	// Find will not fail here, because we tested presence of the option in ID map
	return (*ids.find(option)).second;
}

unsigned int OptionSyntax::getUnusedId() {
	lastId++;
	return lastId;
}

