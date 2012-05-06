#ifndef _ARGLIB_STRING_VALUE_H_
#define _ARGLIB_STRING_VALUE_H_

#include <string>
#include "../Value.h"
#include "../ValueHandle.h"

namespace Arglib {

/// Class StringValue encapsulates type string.
class StringValue : public Value {
	public:
		StringValue(std::string newValue):value(newValue){}
		~StringValue() {}

		void set(std::string newValue) { value = newValue; }
		std::string get() { return value; }
	private:
		std::string value; ///< field to hold the value

};

template <>
std::string ValueHandle::getValue<std::string>();

} // End namespace Arglib

#endif
