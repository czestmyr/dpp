#ifndef _ARGLIB_TYPE_H_
#define _ARGLIB_TYPE_H_

#include <string>
#include "Value.h"

class Type {
	public:
		/// Interprets the string as a value of this type.
		/// If the argument is invalid, an invalid value is returned.
		/// \param argument The argument string to be cast to this type
		/// \return Value instance containing the cast value
		/// \note In subclasses, if the returned value should be of
		/// your own type, create a new instance of the value and
		/// return it to the caller. The ownership of the value is
		/// transferred to the caller.
		virtual Value fromString(const std::string& argument) const = 0;

		/// Makes a clone of this type.
		/// The method should return the new object's pointer cast to Type*
		virtual Type* clone() const = 0;

		template <typename DerivedType>
		static Type* getClone(const DerivedType& type) {
			// Compilation-time checks will ensure that type is derived from Type
			const Type* typePtr = static_cast<const Type*>(&type);
			Type* typeCopy = typePtr->clone();
			return typeCopy;
		}
};

#endif
