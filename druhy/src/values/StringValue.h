#ifndef _ARGLIB_STRING_VALUE_H_
#define _ARGLIB_STRING_VALUE_H_

#include <string>
#include "../Value.h"

class StringValue : public Value {
	public:
		StringValue(std::string newValue):value(newValue);
	private:
		std::string value;

}
#endif
