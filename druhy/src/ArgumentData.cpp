#include "ArgumentData.h"

using namespace std;

bool ArgumentData::addArgument(const string& argument) {
	arguments.push_back(argument);
}

void ArgumentData::setOption(unsigned int optionId, ValueHandle parameter) {
	options.insert(pair<unsigned int, ValueHandle>(optionId, parameter));
}

bool ArgumentData::isOptionSet(unsigned int optionId) const {
	return options.count(optionId) != 0;
}

ValueHandle ArgumentData::getOptionParameter(unsigned int optionId) const {
	map<unsigned int, ValueHandle>::const_iterator it = options.find(optionId);
	if (it == options.end()) {
		return ValueHandle();
	} else {
		return it->second;
	}
}

