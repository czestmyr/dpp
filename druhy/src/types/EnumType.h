#ifndef _ARGLIB_ENUM_TYPE_H_
#define _ARGLIB_ENUM_TYPE_H_

#include "../Type.h"
#include "../Value.h"
#include <set>
#include <string>
#include <vector>

namespace Arglib {

/// Represents enum parameter of an option in command line parameters.
/// It's class derived from Type and overrides methods fromString() and clone().
/// Using method fromString it parses string parametr and converts them to
/// our inner representation of string value represented by class StringValue.
class EnumType: public Type {
	public:
		EnumType();
		~EnumType() {}
	
		/// Adds list of allowed strings.
		/// @param newStrings List of allowed strings given in an vector
		/// that will be added to inner list of allowed strings.
		void addAllowedStrings(const std::vector<std::string>& newStrings);

		/// Adss one allowed string.
		/// @param newString String that will be added to inner list of allowed strings.
		void addAllowedString(const std::string& newString);

		/// Parses option parameter from it's string representation to inner representation of string.
		/// If the argument is invalid, an invalid value is returned.
		/// @param argument String representation of string value to be cast to StringValue type.
		/// When parsing the argument it checks if this argument is defined in the list of allowd strings.
		/// return Pointer to StringValue parsed from given string representation.
		/// @note The ownership of the StringValue is
		/// transferred to the caller and is reference counted further on.
		Value* fromString(const std::string& argument) const;

		/// Makes a clone of this type.
		/// return The method should return the new object's pointer cast to Type*
		Type* clone() const;

	private:
		std::set<std::string> allowedStrings;///< List of strings allowed in this enum
};

} // End namespace Arglib

#endif
