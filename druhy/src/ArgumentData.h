#ifndef _ARGLIB_ARGUMENT_DATA_H_
#define _ARGLIB_ARGUMENT_DATA_H_

#include <string>
#include <vector>
#include <map>
#include "ValueHandle.h"

/// Class that holds data parsed from the arguments, options and their parameters.
/// It stores all the given options with their respective parameters as well as other arguments (which we call
/// regular arguments).
class ArgumentData {
	public:
		/// Adds a regular argument to list of already parsed regular arguments.
		/// @param argument Argument to be added to the list.
		void addArgument(const std::string& argument);

		/// Sets the option, possibly with a value of its parameter.
		/// The ValueHandle can be defaultly constructed, which is default and means no value.
		/// If a Value is provided, it is set as the value for the option's parameter.
		/// If the option is set multiple times, the parameter values are rewritten on each call.
		/// @param optionId Unique id of the option that we want to set.
		/// @param parameter value of the parameter for the option being set.
		void setOption(unsigned int optionId, ValueHandle parameter);

		/// Checks if specified option was set in command line arguments.
		/// @param optionId Unique id of the option we want to check.
		/// @return If the option was set.
		bool isOptionSet(unsigned int optionId) const;

		/// Gets Handle to parameter value specified for the given option.
		/// @param optionId Unique id of option, whose parameter we want to get.
		/// @return ValueHandle representing value of the parameter of the specified option.
		ValueHandle getOptionParameter(unsigned int optionId) const;

		/// Returns all regular arguments stored in this data structure.
		/// @return reference to regular arguments stored in vector of strings.
		const std::vector<std::string>& getArguments() const { return arguments; }

		/// Resets status of this data structure to empty.
		/// Deletes all data alredy stored in data structure and prepares it for next use.
		void resetToEmpty();
	private:
		std::vector<std::string> arguments; ///< List of already stored regular arguments.
		std::map<unsigned int, ValueHandle> options; ///< List of all optionArguments acessible by optionId
};

#endif

