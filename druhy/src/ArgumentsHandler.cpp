#include "ArgumentsHandler.h"

ArgumentsHandler::ArgumentsHandler(){}

void ArgumentsHandler::addOption(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const std::string& helpString) {
	syntax.addOption(optionName, attrib, paramType, helpString);
}

void ArgumentsHandler::addSynonym(const std::string& original, const std::string& synonym) {
	syntax.addSynonym(original, synonym);
}

void ArgumentsHandler::writeHelp() {
	//TODO: Implement
}

void ArgumentsHandler::parse(int argc, char* argv[]) {
	ArgumentParser p(&syntax, &data);
	p.parse(argc, argv);
}

bool ArgumentsHandler::isOptionSet(const std::string& optionName) {
	data.isOptionSet(optionName);
}

Value ArgumentsHandler::getOptionArgument(const std::string& optionName) {
	data.getOptionArgument(optionName);
}

const std::vector<std::string>& ArgumentsHandler::getRegularArguments() {
	data.getArguments();
}

