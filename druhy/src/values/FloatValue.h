#ifndef _ARGLIB_FLOAT_VALUE_H_
#define _ARGLIB_FLOAT_VALUE_H_

#include "../Value.h"

class FloatValue : public Value {
	public:
		FloatValue(float newValue):value(newValue);
	private:
		float value;

}
#endif
