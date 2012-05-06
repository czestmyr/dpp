#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <vector>
#include <map>
#include "ValueHandle.h"

class ArgumentData {
	public:
		/// Adds a regular argument to list of already parsed regular arguments.
		/// @param argument Argument to be added to the list.
		void addArgument(const std::string& argument);

		void setOption(unsigned int optionId, ValueHandle parameter);
		/// Checks if spedified option was set in comand line arguments.
		/// @param optionId Unique id of option we want to check if were set.
		/// @return If the option were set.
		bool isOptionSet(unsigned int optionId) const;

		/// Gets Handle to argument value specified for some option.
		/// @param optionId Unique id of option to which we want get the argument.
		/// @return ValueHandle representing argument given to the specified option.
		ValueHandle getOptionParameter(unsigned int optionId) const;

		/// Returns all regular arguments stored in this data structure.
		/// @return reference to regular arguments stored in vector of strings.
		const std::vector<std::string>& getArguments() const { return arguments; }

		/// Resets status of this data structure to empty.
		/// Deletes all data alredy stored in data structure and prepares it for next use.
		void resetToEmpty();
	private:
		std::vector<std::string> arguments; /// List of already stored regular arguments.
		std::map<unsigned int, ValueHandle> options; /// List of all optionArguments acessible by optionId
};

#endif

