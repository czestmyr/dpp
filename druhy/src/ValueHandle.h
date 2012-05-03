#ifndef _ARGLIB_VALUE_HANDLE_H_
#define _ARGLIB_VALUE_HANDLE_H_

#include "Value.h"

class ValueHandle {
	public:
		ValueHandle();
		ValueHandle(const ValueHandle& other);
		operator=(const ValueHandle& other);
		void setValue(Value* newValue);
		template <class T>
		T getValue() {
			
		}
	private:
		Value* valuePtr;
};

#endif

