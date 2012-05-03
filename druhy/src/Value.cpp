#include "Value.h"

Value::Value(): refCount(0) {}

Value::~Value() {}

void Value::grab() {
	refCount++;
}

void Value::drop() {
	refCount--;
	if (refCount < 0) {
		delete this;
	}
}

