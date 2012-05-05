#include "FrontEnd.h"
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentParser.h"

FrontEnd::FrontEnd() {
	syntax = new OptionSyntax();
	data = new ArgumentData();
}

FrontEnd::~FrontEnd() {
	delete data;
	delete syntax;
}

void FrontEnd::addSynonym(const std::string& original, const std::string& synonym) {
	syntax->addSynonym(original, synonym);
}

void FrontEnd::writeOptionHelp(std::ostream& stream, int terminalSize) {
	syntax->writeHelp(stream, terminalSize);
}

void FrontEnd::parse(int argc, const char* argv[]) {
	ArgumentParser p(syntax, data);
	p.parse(argc, argv);
}

bool FrontEnd::isOptionSet(const std::string& optionName) const {
	unsigned int id = syntax->getId(optionName);
	data->isOptionSet(id);
}

const std::vector<std::string>& FrontEnd::getRegularArguments() const {
	data->getArguments();
}

void FrontEnd::addOptionInternal(const std::string& optionName, ParameterAttribute attrib, Type* paramType, const std::string& helpString) {
	syntax->addOption(optionName, attrib, paramType, helpString);
}

