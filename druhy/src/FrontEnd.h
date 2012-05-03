#ifndef _ARGLIB_FRONT_END_H_
#define _ARGLIB_FRONT_END_H_

#include <string>
#include <vector>

#include "ParameterAttribute.h"
#include "Value.h"
#include "IType.h"
#include "types/DummyType.h"

class OptionSyntax;
class ArgumentData;

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
			IType* typeCopy = IType::getClone(paramType);
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
		Value getOptionParameter(const std::string& optionName) const;
		const std::vector<std::string>& getRegularArguments() const;

	private:
		void addOptionInternal(const std::string& optionName, ParameterAttribute attrib, IType* paramType, const std::string& helpString);

		OptionSyntax* syntax;	
		ArgumentData* data;
};

#endif
