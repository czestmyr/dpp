#include "ArgumentsHandler.h"

ArgumentsHandler::ArgumentsHandler(){}

void ArgumentsHandler::addOption(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const std::string& helpString) {
	syntax.addOption(optionName, attrib, paramType, helpString);
}
void ArgumentsHandler::addSynonym(const std::string& original, const std::string& synonym) {
	syntax.addSynonym(original, synonym);
}
ParameterAttribute ArgumentsHandler::getAttribute(const std::string& option) const {
	//TODO: implement
}
const IType* ArgumentsHandler::getType(const std::string& option) const {
	//TODO: implement
}
const std::string& ArgumentsHandler::getHelp(const std::string& option) const {
	//TODO: implement
}
