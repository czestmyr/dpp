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
		/// This method has to be here because without a type specification, the compiler
		/// does not know, which template instance of addOption it has to create.
		void addOption(const std::string& optionName, OptionAttribute optionAttrib = OPTION_ALLOWED) {
			addOption(optionName, optionAttrib, DummyType(), PARAM_FORBIDDEN);
		}

		void addSynonym(const std::string& original, const std::string& synonym);

		void setOptionHelp(const std::string& option, const std::string& help);
		void writeHelp(std::ostream& stream, int terminalSize = 80) const;
		void parse(int argc, const char* argv[]);

		bool isOptionSet(const std::string& optionName) const;

		// TODO: What to do with the cast exception?
		template <class ValueType>
		ValueType getOptionParameter(const std::string& optionName) const {
			unsigned int id = syntax->getId(optionName);
			ValueHandle valueHandle = data->getOptionParameter(id);
		
			if (valueHandle.isEmpty()) {
				// TODO: throw exception
			}

			return valueHandle.getValue<ValueType>();
		}

		const std::vector<std::string>& getRegularArguments() const;

	private:
		void addOptionInternal(const std::string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute attrib);

		OptionSyntax* syntax;	
		ArgumentData* data;
};

#endif
