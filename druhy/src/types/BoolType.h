#ifndef _ARGLIB_BOOL_TYPE_H_
#define _ARGLIB_BOOL_TYPE_H_

#include "../Type.h"
#include "../Value.h"

namespace Arglib {

/// Represents boolean parameter of an option in command line parameters.
/// It's class derived from Type and overrides methods fromString() and clone().
/// Using method fromString it parses string parametr and converts them to
/// our inner representation of boolean value represented by class BoolValue.
class BoolType: public Type {
	public:
		BoolType();
		~BoolType() {}

		/// Parses option parameter from it's string representation to our representation of boolean.
		/// If the argument is invalid, an invalid value is returned.
		/// @param argument String representation of boolean value to be cast to this type.
		/// return Pointer to BoolValue parsed from given string representation.
		/// @note The ownership of the Boolvalue is
		/// transferred to the caller and is reference counted further on.
		Value* fromString(const std::string& argument) const;
		
		/// Makes a clone of this type.
		/// return The method should return the new object's pointer cast to Type*
		Type* clone() const;

	private:
};

} // End namespace Arglib

#endif
