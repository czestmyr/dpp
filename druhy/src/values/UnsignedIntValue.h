#ifndef _ARGLIB_UNSIGNED_INT_VALUE_H_
#define _ARGLIB_UNSIGNED_INT_VALUE_H_

#include "../Value.h"

class UnsignedIntValue : public Value {
	public:
		UnsignedIntValue(unsigned int newValue):value(newValue);
	private:
		unsigned int value;


}
#endif
