#ifndef _ARGLIB_INT_VALUE_H_
#define _ARGLIB_INT_VALUE_H_

#include "../Value.h"
#include "../ValueHandle.h"

class IntValue: public Value {
	public:
		IntValue(int newValue): value(newValue) {}
		~IntValue() {}

		void set(int newValue) { value = newValue; }
		int get() { return value; }
	private:
		int value;
};

//TODO: Exception!
template <>
int ValueHandle::getValue<int>() {
	IntValue* intValue = dynamic_cast<IntValue*>(valuePtr);
	return intValue->get();
};

#endif
