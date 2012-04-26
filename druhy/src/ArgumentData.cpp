#include "ArgumentData.h"

bool ArgumentData::addArgument(const std::string& argument) {
	arguments.push_back(argument);
}

bool ArgumentData::isOptionSet(const std::string& optionName){
	// TODO: implement
}

Value ArgumentData::getOptionArgument(const std::string& optionName){
	// TODO: implement
}
