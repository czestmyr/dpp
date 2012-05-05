#ifndef _ARGLIB_LONG_VALUE_H_
#define _ARGLIB_LONG_VALUE_H_

#include "../Value.h"

class LongValue : public Value {
	public:
		LongValue(long newValue):value(newValue);
		~LongValue() {}

	private:
		float value;


}
#endif
