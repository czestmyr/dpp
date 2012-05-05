#ifndef _ARGLIB_DOUBLE_VALUE_H_
#define _ARGLIB_DOUBLE_VALUE_H_

#include "../Value.h"

class DoubleValue : public Value {
	public:
		DoubleValue(double newValue):value(newValue);
		DoubleValue() {}

	private:
		double value;


}
#endif
