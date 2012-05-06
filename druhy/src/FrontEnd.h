#ifndef _ARGLIB_FRONT_END_H_
#define _ARGLIB_FRONT_END_H_

#include <string>
#include <vector>
#include <iostream>

#include "ParameterAttribute.h"
#include "OptionAttribute.h"
#include "ValueHandle.h"
#include "Type.h"
#include "types/DummyType.h"
#include "OptionSyntax.h"
#include "ArgumentData.h"

class FrontEnd {
	public:
		FrontEnd();
		FrontEnd(const FrontEnd& other);
		~FrontEnd();

		FrontEnd& operator=(const FrontEnd& other);

		/// TODO: Document, what a "DerivedType" is
		/// Adds new option witch all its properties specified by the user.
		/// 
		/// @param DefivedType Type specifiing which arguments can be added to the option.
		///	It must be class derived from class Type.
		/// @param optionName Name of option to be added to set of known options.
		/// @param optionAttrib Spedifier defining if option is allowed or required.
		///	Possible values are OPTION_ALLOWED and OPTION_REQUIRED.
		/// @param paramType Allows the user to define type without any knowledge of templates. TODO: write better 
		/// @param paramAttrib Specifier defining if option arguments are required, allowed or forbidden.
		///	Possible values are PARAM_REQUIRED, PARAM_ALLOWED amd PARAM_FORBIDDEN
		template <class DerivedType>
		void addOption(
			const std::string& optionName,
			OptionAttribute optionAttrib,
			const DerivedType& paramType,
			ParameterAttribute paramAttrib
		) {
			Type* typeCopy = Type::getClone(paramType);
			addOptionInternal(optionName, optionAttrib, typeCopy, paramAttrib);
		}

		/// Special case of addOption method when only option name is specified.
		/// This method adds options which can't have any parameters.
		/// This method has to be here because without a type specification, the compiler
		/// does not know, which template instance of addOption it has to create.
		/// @param optionName Name of option to be added to set of known options.
		/// @param optionAttrib Spedifier defining if option is allowed or required.
		///	Possible values are OPTION_ALLOWED and OPTION_REQUIRED.
		///	Default value is OPTION_ALLOWED
		void addOption(const std::string& optionName, OptionAttribute optionAttrib = OPTION_ALLOWED) {
			addOptionInternal(optionName, optionAttrib, Type::getClone(DummyType()), PARAM_FORBIDDEN);
		}

		/// Defines synonyms between options.
		/// The original option must be already defined.
		/// Original can be previously defined synonym too.
		/// Synonym can be in long or short form.
		/// @param original Alredy specified option to which we want to add a synonym.
		/// @param synonym Name of option which should be synonym for original.
		void addSynonym(const std::string& original, const std::string& synonym);

		/// Assignss help to specified option.
		/// @param optionName Name of option to which add the help.
		/// @param help Text of help to assign.
		void setOptionHelp(const std::string& optionName, const std::string& help);

		/// Writes help to all specified options and format it to desired width.
		/// @param stream Stream to which should be the help written.
		/// @param terminalSize Width of the terminal in characters.
		///	The help will be wrapped to this number of characters.
		void writeHelp(std::ostream& stream, int terminalSize = 80) const;

		/// Parse arguments stored in @param argv.
		/// @param argc Number of tokens in argv.
		/// @param argv Command line parameters given to the program.
		/// 	They have to start with name of the program,
		///	because this is common for agguments in C++.
		void parse(int argc, const char* argv[]);

		/// Tests if the option @param optionName was given.
		/// @param optionName Name of the option to be tested if given.
		/// @return If option optionName was given.
		bool isOptionSet(const std::string& optionName) const;

		/// Tests if the parameter to option @param optionName was given.
		/// @param optionName Name of the option to be tested for parameter.
		/// @return If a parameter to option optionName was given.
		bool isOptionParameterSet(const std::string& optionName) const;

		/// This method gets parameter of option specified by optionName.
		/// It returns the value of the argument transformed to ValueType specified by the user.
		/// @param ValueType Specifies a type of return value expected by the user.
		/// @param optionName Name of the option to which return the argument. 
		/// @return Value of the argument casted to type ValueType
		template <class ValueType>
		ValueType getOptionParameter(const std::string& optionName) const {
			unsigned int id = syntax->getId(optionName);
			ValueHandle valueHandle = data->getOptionParameter(id);
			if (valueHandle.isEmpty()) {
				throw ArgumentException("No parametr were added to this option.");
			}
		
			return valueHandle.getValue<ValueType>();
		}

		/// Returns all regular arguments parsed in last call of function parse.
		/// @return reference to regular arguments stored in vector of strings 
		const std::vector<std::string>& getRegularArguments() const;

	private:
		/// Separates adding new option in frontEnd and our internal representations of option syntax.
		/// @param optionName Name of option to be added in set of known options.
		/// @param optionAttrib Spedifier defining if option is allowed or required.
		///	Possible values are OPTION_ALLOWED and OPTION_REQUIRED.
		/// @param paramType Specifies a type of parameter. This type must be derived from type Type. 
		/// @param paramAttrib Specifier defining if option arguments are required, allowed or forbidden.
		///	Possible values are PARAM_REQUIRED, PARAM_ALLOWED amd PARAM_FORBIDDEN
		void addOptionInternal(
			const std::string& optionName, 
			OptionAttribute optionAttrib, 
			Type* paramType, 
			ParameterAttribute paramAttrib
		);
		
		OptionSyntax* syntax; /// Stores syntax of options defined by the user.
		ArgumentData* data; /// Stores all regular arguments given in parameters.
};

#endif
