#ifndef _ARGLIB_BOOL_VALUE_H_
#define _ARGLIB_BOOL_VALUE_H_

#include "../Value.h"
#include "../ValueHandle.h"

class BoolValue: public Value {
	public:
		BoolValue(bool newValue): value(newValue) {}
		~BoolValue() {}

		void set(bool newValue) { value = newValue; }
		bool get() { return value; }
	private:
		bool value;
};

template <> bool ValueHandle::getValue<bool>();

#endif
