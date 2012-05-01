#include "ArgumentData.h"

bool ArgumentData::addArgument(const std::string& argument) {
	arguments.push_back(argument);
}

void ArgumentData::setOption(unsigned int optionId, const Value& parameter) {

}

bool ArgumentData::isOptionSet(unsigned int optionId){
	// TODO: implement
}

Value ArgumentData::getOptionParameter(unsigned int optionId){
	// TODO: implement
}
