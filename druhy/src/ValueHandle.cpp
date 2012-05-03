#include "ValueHandle.h"

ValueHandle::ValueHandle(Value* newValue) {
	if (newValue != NULL) {
		newValue->grab();
	}
	valuePtr = newValue;
}

ValueHandle::~ValueHandle() {
	if (valuePtr != NULL) {
		valuePtr->drop();
	}
}

ValueHandle::ValueHandle(const ValueHandle& other) {
	if (other.valuePtr != NULL) {
		other.valuePtr->grab();
	}
	valuePtr = other.valuePtr;
}

ValueHandle& ValueHandle::operator=(const ValueHandle& other) {
	setValue(other.valuePtr);
}

void ValueHandle::setValue(Value* newValue) {
	if (valuePtr != NULL) {
		// We already point to some value
		valuePtr->drop();
	}

	if (newValue != NULL) {
		newValue->grab();
	}
	valuePtr = newValue;
}

bool ValueHandle::isEmpty() {
	return valuePtr == NULL;
}

