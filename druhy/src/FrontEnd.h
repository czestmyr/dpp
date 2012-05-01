#ifndef _ARGLIB_FRONT_END_H_
#define _ARGLIB_FRONT_END_H_

#include <string>
#include <vector>
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentParser.h"


class FrontEnd {
	public:
		FrontEnd();

		void addOption(const std::string& optionName, ParameterAttribute attrib = FORBIDDEN, IType* paramType = NULL, const std::string& helpString = "");
		void addSynonym(const std::string& original, const std::string& synonym);

		void writeHelp();
		void parse(int argc, const char* argv[]);

		bool isOptionSet(const std::string& optionName) const;
		Value getOptionParameter(const std::string& optionName) const;
		const std::vector<std::string>& getRegularArguments() const; 
	private:
		OptionSyntax syntax;	
		ArgumentData data;
};

#endif
