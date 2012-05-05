#ifndef _ARGLIB_ENUM_TYPE_H_
#define _ARGLIB_ENUM_TYPE_H_

#include "../Type.h"
#include "../Value.h"
#include <set>
#include <string>
#include <vector>

class EnumType: public Type {
	public:
		EnumType();
		
		void AddAllowedStrings(const std::vector<std::string>& newStrings);
		void AddAllowedString(const std::string& newString);


		Value* fromString(const std::string& argument) const;
		Type* clone() const;

	private:
		std::set<std::string> allowedStrings;
};

#endif
