#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <map>
#include <iostream>
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

		void writeHelp(std::ostream& stream) const;

		unsigned int getId(const std::string& option) const;
	private:
		unsigned int getUnusedId();
		unsigned int lastId;

		std::map<std::string, unsigned int> ids;
		std::multimap<unsigned int, std::string> synonyms;
		std::map<unsigned int, ParameterAttribute> attributes;
		std::map<unsigned int, Type*> types;
		std::map<unsigned int, std::string> helpStrings;
};

#endif

