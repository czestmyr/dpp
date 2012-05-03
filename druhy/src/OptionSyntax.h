#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <map>
#include "Type.h"
#include "ParameterAttribute.h"

class OptionSyntax {
	public:
		OptionSyntax();
		~OptionSyntax();

		void addOption(const std::string& optionName, ParameterAttribute attrib = FORBIDDEN, Type* paramType = NULL, const std::string& helpString = "");
		void addSynonym(const std::string& original, const std::string& synonym);

		ParameterAttribute getAttribute(const std::string& option) const;
		const Type* getType(const std::string& option) const;
		const std::string& getHelp(const std::string& option) const;

		unsigned int getId(const std::string& option) const;
	private:
		unsigned int getUnusedId();
		unsigned int lastId;

		std::map<std::string, unsigned int> ids;
		std::map<unsigned int, ParameterAttribute> attributes;
		std::map<unsigned int, Type*> types;
		std::map<unsigned int, std::string> helpStrings;
};

#endif

