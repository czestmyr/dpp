#include "ArgumentData.h"

using namespace std;

bool ArgumentData::addArgument(const string& argument) {
	arguments.push_back(argument);
}

void ArgumentData::setOption(unsigned int optionId, const Value& parameter) {
	options.insert(pair<unsigned int, Value>(optionId, parameter));
}

bool ArgumentData::isOptionSet(unsigned int optionId) const {
	return options.count(optionId) != 0;
}

Value ArgumentData::getOptionParameter(unsigned int optionId) const {
	map<unsigned int, Value>::const_iterator it = options.find(optionId);
	if (it == options.end()) {
		return Value();
	} else {
		return (*it).second;
	}
}

