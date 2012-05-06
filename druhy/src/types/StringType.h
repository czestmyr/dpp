#ifndef _ARGLIB_STRING_TYPE_H_
#define _ARGLIB_STRING_TYPE_H_

#include "../Type.h"
#include "../Value.h"

/// Represents string parameter of an option in command line parameters.
/// It's class derived from Type and overrides methods fromString() and clone().
/// Using method fromString it parses string parametr and converts them to
/// our inner representation of string value represented by class StringValue.
class StringType: public Type {
	public:
		StringType();
		~StringType() {}

		/// Parses option parameter from it's string representation to inner representation of string.
		/// If the argument is invalid, an invalid value is returned.
		/// @param argument String representation of string value to be cast to StringValue type.
		/// return Pointer to StringValue parsed from given string representation.
		/// @note The ownership of the StringValue is
		/// transferred to the caller and is reference counted further on.
		Value* fromString(const std::string& argument) const;
		
		/// Makes a clone of this type.
		/// return The method should return the new object's pointer cast to Type*
		Type* clone() const;

	private:
};

#endif
