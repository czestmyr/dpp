#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <map>
#include "IType.h"
#include "ParameterAttribute.h"

class OptionSyntax {
	public:
		OptionSyntax();

		// TODO: So far, type will be owned by the OptionSyntax. Make it better in the future
		void addOption(const std::string& optionName, ParameterAttribute attrib = FORBIDDEN, IType* paramType = NULL, const std::string& helpString = "");
		void addSynonym(const std::string& original, const std::string& synonym);

		ParameterAttribute getAttribute(const std::string& option) const;
		const IType* getType(const std::string& option) const;
		const std::string& getHelp(const std::string& option) const;

		unsigned int getId(const std::string& option) const;
	private:
		unsigned int getUnusedId();
		unsigned int lastId;

		std::map<std::string, unsigned int> ids;
		std::map<unsigned int, ParameterAttribute> attributes;
		std::map<unsigned int, IType*> types;
		std::map<unsigned int, std::string> helpStrings;
};

#endif

