#ifndef _ARGLIB_STRING_VALUE_H_
#define _ARGLIB_STRING_VALUE_H_

#include <string>
#include "../Value.h"
#include "../ValueHandle.h"
#include "../ArgumentException.h"

class StringValue : public Value {
	public:
		StringValue(std::string newValue):value(newValue){}
		~StringValue(){}
				void set(std::string newValue) { value = newValue; }
		std::string get() { return value; }
	private:
		std::string value;

};

//TODO: Add proper information to this exception!
template <>
std::string ValueHandle::getValue<std::string>() {
		StringValue* stringValue = dynamic_cast<StringValue*>(valuePtr);
		if( stringValue == NULL ) {
			throw ArgumentException("Type defined with this option doesn't match type required by this function.");
		}
		return stringValue->get();

};
#endif
