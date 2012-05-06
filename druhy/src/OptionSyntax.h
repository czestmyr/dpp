#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <set>
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
		OptionSyntax(const OptionSyntax& other);
		~OptionSyntax();

		/// Assignment operator.
		/// The old options that were saved into this object are deleted and the whole syntax is copied fron
		/// the other object.
		/// @param other The object from which to copy the syntax.
		/// @return Reference to this OptionSyntax object.
		OptionSyntax& operator=(const OptionSyntax& other);

		/// Adds an option to the syntax held by this object.
		/// @param optionName Name of the newly added option.
		/// @param optionAttrib The attribute of the new option.
		///	Possible values are OPTION_ALLOWED and OPTION_REQUIRED.
		/// @param paramType Pointer to a Type instance that specifies type of this option's parameter.
		///	The ownership of the Type instance is transfered to the OptionSyntax object.
		/// @param paramAttrib Attribute of the parameter. Defines whether the parameter is optional,
		///	allowed or required. Possible values are PARAM_REQUIRED, PARAM_ALLOWED amd PARAM_FORBIDDEN
		void addOption(const std::string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib);

		/// Adds an option that is synonymous to another option.
		/// All the properties (option attribute and parameter type and attribute) are retained from the
		/// original option. This basically just specifies another way to set the option.
		/// @param original Name of the original option (e.g. "version")
		/// @param synonym Name of the synonym (e.g. "v")
		void addSynonym(const std::string& original, const std::string& synonym);

		/// Returns the attribute of the given option.
		/// The option can be specified by any of the so-far defined synonyms for it.
		/// @param option Name of the option.
		/// @return attribute that says whether the option is allowed or required.
		ParameterAttribute getAttribute(const std::string& option) const;

		/// Returns the type of the parameter of a given option.
		/// @param option The name of the option
		/// @return Type of the option's parameter. If the option has no parameter, DummyType is returned.
		const Type* getParameterType(const std::string& option) const;

		void setOptionHelp(const std::string& option, const std::string& helpString);
		void writeHelp(std::ostream& stream, int terminalSize) const;

		unsigned int getId(const std::string& option) const;

		const std::set<unsigned int>& getRequiredOptions() const;
	private:
		void deinit();
		void initFrom(const OptionSyntax& other);

		unsigned int getUnusedId();
		unsigned int lastId;

		bool isOptionDefined(const std::string& optionName) const;

		void writeSynonyms(unsigned int id, std::ostream& stream) const;
		void writeParameter(unsigned int id, std::ostream& stream) const;
		void writeWithLimit(std::string& string, int limit, std::ostream& stream) const;
		void writeOutLine(StrListIt lineBegin, StrListIt lineEnd, std::ostream& stream) const;

		std::map<std::string, unsigned int> ids;
		std::multimap<unsigned int, std::string> synonyms;
		std::map<unsigned int, ParameterAttribute> paramAttributes;
		std::map<unsigned int, Type*> types;
		std::map<unsigned int, std::string> helpStrings;

		std::set<unsigned int> requiredOptions;
};

#endif

