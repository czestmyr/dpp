#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <vector>
#include <map>
#include "Value.h"

class ArgumentData {
	public:
		bool addArgument(const std::string& argument);

		void setOption(unsigned int optionId, const Value& parameter);
		bool isOptionSet(unsigned int optionId) const;

		Value getOptionParameter(unsigned int optionId) const;

		const std::vector<std::string>& getArguments() const { return arguments; }
	private:
		std::vector<std::string> arguments;
		std::map<unsigned int, Value> options;
};

#endif

