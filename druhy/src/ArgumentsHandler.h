#ifndef _ARGLIB_ARGUMENTS_HANDLER_H_
#define _ARGLIB_ARGUMENTS_HANDLER_H_

#include <string>
#include <vector>
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentParser.h"


class ArgumentsHandler {
	public:
		ArgumentsHandler();

		void addOption(const std::string& optionName, ParameterAttribute attrib = FORBIDDEN, IType* paramType = NULL, const std::string& helpString = "");
		void addSynonym(const std::string& original, const std::string& synonym);

		void writeHelp();
		void parse(int argc, char* argv[]);

		bool isOptionSet(const std::string& optionName);
		Value getOptionArgument(const std::string& optionName);
		// TODO: Shouldn't we use typedef for this crazy type?
		std::vector<std::string> getRegularArguments();
	private:
		OptionSyntax syntax;	
		ArgumentData data;
};

#endif
