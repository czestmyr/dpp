#ifndef _ARGLIB_UNSIGNED_LONG_VALUE_H_
#define _ARGLIB_UNSIGNED_LONG_VALUE_H_

#include "../Value.h"

class UnsignedLongValue : public Value {
	public:
		UnsignedLongValue(unsigned long newValue):value(newValue);
	private:
		unsigned long value;


}
#endif
