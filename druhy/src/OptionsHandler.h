#ifndef _ARGLIB_OPTIONS_HANDLER_H_
#define _ARGLIB_OPTIONS_HANDLER_H_

#include <string>
#include "OptionSyntax.h"
#include "ArgumentData.h"
#include "ArgumentParser.h"


class OptionsHandler {
	public:
		OptionsHandler();

		void addOption(const std::string& optionName, ParameterAttribute attrib = FORBIDDEN, IType* paramType = NULL, const std::string& helpString = "");
		void addSynonym(const std::string& original, const std::string& synonym);

		ParameterAttribute getAttribute(const std::string& option) const;
		const IType* getType(const std::string& option) const;
		const std::string& getHelp(const std::string& option) const;
	private:
		OptionSyntax syntax;	
		ArgumentData data;
};

#endif
