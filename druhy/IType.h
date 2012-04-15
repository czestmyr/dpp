#ifndef _ARGLIB_INTERFACE_TYPE_H_
#define _ARGLIB_INTERFACE_TYPE_H_

#include <string>

class IType {
	public:
		/// Tells whether the given argument conforms to the type.
		/// \param argument The argument to check
		/// \return whether the given argument conforms to this type.
		virtual bool conforms(const std::string& argument);

		/// Interprets the string as a value of this type.
		/// \param argument The argument string to be cast to this type
		/// \return Value instance containing the cast value
		/// \note In subclasses, if the returned value should be of
		/// your own type, create a new instance of the value and
		/// return it to the caller. The ownership of the value is
		/// transferred to the caller.
		virtual Value fromString(const std::string& argument);
};

#endif

