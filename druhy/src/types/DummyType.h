#ifndef _ARGLIB_DUMMY_TYPE_H_
#define _ARGLIB_DUMMY_TYPE_H_

#include "../Type.h"
#include "../ArgumentException.h"

using namespace std;

namespace Arglib {

/// Represents undefined parameter type of an option in command line parameters.
/// It's class derived from Type and overrides methods fromString() and clone().
/// Calling method fromString throws an exception, because it isn't possible to parse
/// to undefined type.
class DummyType: public Type {
	public:
		~DummyType() {}

		/// Trhows an Exception becase parsing string to undefined type isn't possible.
		/// It throws and exception independently on the argument.
		/// @param argument String representation of parameter value.
		/// return Doesn't return becase of throwing an excpetion.
		Value* fromString(const string& argument) const {
			throw ArgumentException(string("Option parameter \"") + argument + "\" would have an unspecified type");
		};

		/// Makes a clone of this type.
		/// return The method should return the new object's pointer cast to Type*
		Type* clone() const {
			return new DummyType(*this);
		}
};

} // End namespace Arglib

#endif

