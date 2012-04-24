#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <list>

class ArgumentData {
	public:
		bool addArgument(const std::string& argument);

		const std::list<std::string>& getArguments() const { return arguments; }
	private:
		std::list<std::string> arguments;
};

#endif

