#ifndef _ARGLIB_INT_TYPE_H_
#define _ARGLIB_INT_TYPE_H_

#include "../Type.h"
#include "../Value.h"

/// Represents integer parameter of an option in command line parameters.
/// It's class derived from Type and overrides methods fromString() and clone().
/// Using method fromString it parses string parametr and converts them to
/// our inner representation of integer value represented by class IntValue.
class IntType: public Type {
	public:
		IntType();
		~IntType() {}
		/// Activates low bound of this type and sets its value.
		/// @param bound Value to that will be set the low bound.
		void setLowBound(int bound);
		/// Activates high bound of this type and sets its value.
		/// @param bound Value to that will be set the high bound.
		void setHighBound(int bound);

		/// Parses option parameter from it's string representation to inner representation of integer.
		/// If the argument is invalid, an invalid value is returned.
		/// @param argument String representation of integer value to be cast to IntValue type.
		/// return Pointer to IntValue parsed from given string representation.
		/// @note The ownership of the IntValue is
		/// transferred to the caller and is reference counted further on.
		Value* fromString(const std::string& argument) const;

		/// Makes a clone of this type.
		/// return The method should return the new object's pointer cast to Type*
		Type* clone() const;

	private:
		bool hasLowBound; ///< Is low bound for this type defined.
		bool hasHighBound; ///< Is high bound for this type defined.
		int lowBound; ///< Low bound of this integer type.
		int highBound; ///< High bound of this integer type.
};

#endif
