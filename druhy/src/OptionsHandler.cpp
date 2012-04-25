#include "OptionsHandler.h"

OptionsHandler::OptionsHandler(){}

void OptionsHandler::addOption(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const std::string& helpString) {
	syntax.addOption(optionName, attrib, paramType, helpString);
}
void OptionsHandler::addSynonym(const std::string& original, const std::string& synonym) {
	syntax.addSynonym(original, synonym);
}
ParameterAttribute OptionsHandler::getAttribute(const std::string& option) const {
	//TODO: implement
}
const IType* OptionsHandler::getType(const std::string& option) const {
	//TODO: implement
}
const std::string& OptionsHandler::getHelp(const std::string& option) const {
	//TODO: implement
}
