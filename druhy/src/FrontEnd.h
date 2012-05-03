#ifndef _ARGLIB_FRONT_END_H_
#define _ARGLIB_FRONT_END_H_

#include <string>
#include <vector>

#include "ParameterAttribute.h"
#include "ValueHandle.h"
#include "Type.h"
#include "types/DummyType.h"
#include "OptionSyntax.h"
#include "ArgumentData.h"

class FrontEnd {
	public:
		FrontEnd();
		~FrontEnd();

		/// TODO: Document, what a "DerivedType" is
		template <class DerivedType>
		void addOption(
			const std::string& optionName,
			ParameterAttribute attrib,
			const DerivedType& paramType,
			const std::string& helpString = ""
		) {
			Type* typeCopy = Type::getClone(paramType);
			addOptionInternal(optionName, attrib, typeCopy, helpString);
		}

		/// Special case of addOption method when only option name is specified.
		/// This method has to be here because without a type specification, the compiler
		/// does not know, which template instance of addOption it has to create.
		void addOption(const std::string& optionName) {
			addOption(optionName, FORBIDDEN, DummyType(), "");
		}

		void addSynonym(const std::string& original, const std::string& synonym);

		void writeHelp();
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
		void addOptionInternal(const std::string& optionName, ParameterAttribute attrib, Type* paramType, const std::string& helpString);

		OptionSyntax* syntax;	
		ArgumentData* data;
};

#endif
