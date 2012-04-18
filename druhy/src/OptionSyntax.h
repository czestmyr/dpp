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
		void addOption(const std::string& optionName, ParameterAttribute attrib = ALLOWED, IType* type = NULL);
		bool setSynonymous(const std::string& option1, const std::string& option2);
		bool setOptionHelp(const std::string& optionName, const std::string& helpString);

		bool wasAdded(const std::string& option) const;
		ParameterAttribute getAttribute(const std::string& option) const;
		const IType* getType(const std::string& option) const;
		const std::string& getHelp(const std::string& option) const;
	private:
		unsigned int getUnusedId();
		unsigned int lastId;

		std::map<std::string, unsigned int> ids;
		std::map<unsigned int, ParameterAttribute> attributes;
		std::map<unsigned int, IType*> types;
		std::map<unsigned int, std::string> helpStrings;

		static std::string emptyHelp;
};

#endif

