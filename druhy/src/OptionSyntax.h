#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "Type.h"
#include "ParameterAttribute.h"
#include "OptionAttribute.h"

typedef std::list<std::string>::iterator StrListIt;

class OptionSyntax {
	public:
		OptionSyntax();
		~OptionSyntax();

		void addOption(const std::string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib);
		void addSynonym(const std::string& original, const std::string& synonym);

		ParameterAttribute getAttribute(const std::string& option) const;
		const Type* getType(const std::string& option) const;

		void setOptionHelp(const std::string& option, const std::string& helpString);
		void writeHelp(std::ostream& stream, int terminalSize) const;

		unsigned int getId(const std::string& option) const;
	private:
		unsigned int getUnusedId();
		unsigned int lastId;

		bool isOptionDefined(const std::string& optionName) const;

		void writeSynonyms(unsigned int id, std::ostream& stream) const;
		void writeWithLimit(std::string& string, int limit, std::ostream& stream) const;
		void writeOutLine(StrListIt lineBegin, StrListIt lineEnd, std::ostream& stream) const;

		std::map<std::string, unsigned int> ids;
		std::multimap<unsigned int, std::string> synonyms;
		std::map<unsigned int, OptionAttribute> optionAttributes; 
		std::map<unsigned int, ParameterAttribute> paramAttributes;
		std::map<unsigned int, Type*> types;
		std::map<unsigned int, std::string> helpStrings;
};

#endif

