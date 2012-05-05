#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <vector>
#include <map>
#include "ValueHandle.h"

class ArgumentData {
	public:
		bool addArgument(const std::string& argument);

		void setOption(unsigned int optionId, ValueHandle parameter);
		bool isOptionSet(unsigned int optionId) const;

		ValueHandle getOptionParameter(unsigned int optionId) const;

		const std::vector<std::string>& getArguments() const { return arguments; }

		void resetToEmpty();
	private:
		std::vector<std::string> arguments;
		std::map<unsigned int, ValueHandle> options;
};

#endif

