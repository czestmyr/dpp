#include "FrontEnd.h"
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentParser.h"

using namespace std;

FrontEnd::FrontEnd() {
	syntax = new OptionSyntax();
	data = new ArgumentData();
}

FrontEnd::FrontEnd(const FrontEnd& other) {
	syntax = new OptionSyntax(*other.syntax);
	data = new ArgumentData(*other.data);
}

FrontEnd::~FrontEnd() {
	delete data;
	delete syntax;
}

FrontEnd& FrontEnd::operator=(const FrontEnd& other) {
	delete data;
	delete syntax;
	syntax = new OptionSyntax(*other.syntax);
	data = new ArgumentData(*other.data);
}

void FrontEnd::addSynonym(const string& original, const string& synonym) {
	syntax->addSynonym(original, synonym);
}

void FrontEnd::setOptionHelp(const string& option, const string& help) {
	syntax->setOptionHelp(option, help);
}

void FrontEnd::writeHelp(ostream& stream, int terminalSize) const {
	syntax->writeHelp(stream, terminalSize);
}

void FrontEnd::parse(int argc, const char* argv[]) {
	ArgumentParser p(syntax, data);
	p.parse(argc, argv);
}

bool FrontEnd::isOptionSet(const string& optionName) const {
	unsigned int id = syntax->getId(optionName);
	data->isOptionSet(id);
}

bool FrontEnd::isOptionParameterSet(const string& optionName) const {
	unsigned int id = syntax->getId(optionName);
	ValueHandle valueHandle = data->getOptionParameter(id);
	return !valueHandle.isEmpty();
}

const vector<string>& FrontEnd::getRegularArguments() const {
	data->getArguments();
}

void FrontEnd::addOptionInternal(const string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib) {
	syntax->addOption(optionName, optionAttrib, paramType, paramAttrib);
}

