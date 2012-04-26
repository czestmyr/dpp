#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <vector>

class ArgumentData {
	public:
		bool addArgument(const std::string& argument);

		bool isOptionSet(const std::string& optionName);

		Value getOptionArgument(const std::string& optionName);

		const std::vector<std::string>& getArguments() const { return arguments; }
	private:
		std::vector<std::string> arguments;
};

#endif

