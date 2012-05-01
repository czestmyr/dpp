#include "FrontEnd.h"

FrontEnd::FrontEnd(){}

void FrontEnd::addOption(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const std::string& helpString) {
	syntax.addOption(optionName, attrib, paramType, helpString);
}

void FrontEnd::addSynonym(const std::string& original, const std::string& synonym) {
	syntax.addSynonym(original, synonym);
}

void FrontEnd::writeHelp() {
	//TODO: Implement
}

void FrontEnd::parse(int argc, const char* argv[]) {
	ArgumentParser p(&syntax, &data);
	p.parse(argc, argv);
}

bool FrontEnd::isOptionSet(const std::string& optionName) const {
	unsigned int id = syntax.getId(optionName);
	data.isOptionSet(id);
}

Value FrontEnd::getOptionParameter(const std::string& optionName) const {
	unsigned int id = syntax.getId(optionName);
	data.getOptionParameter(id);
}

const std::vector<std::string>& FrontEnd::getRegularArguments() const {
	data.getArguments();
}

