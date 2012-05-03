#ifndef _ARGLIB_VALUE_HANDLE_H_
#define _ARGLIB_VALUE_HANDLE_H_

#include "Value.h"

class ValueHandle {
	public:
		ValueHandle(Value* newValue = NULL);
		ValueHandle(const ValueHandle& other);

		~ValueHandle();

		ValueHandle& operator=(const ValueHandle& other);

		void setValue(Value* newValue);
		template <class T>
		T getValue();

		bool isEmpty();
	private:
		Value* valuePtr;
};

#endif

