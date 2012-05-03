#ifndef _ARGLIB_INT_VALUE_H_
#define _ARGLIB_INT_VALUE_H_

#include "../Value.h"

class IntValue : public Value {
	public:
		IntValue(int newValue):value(newValue);
	private:
		int value;
}
#endif
