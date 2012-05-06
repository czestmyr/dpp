#include "Value.h"

namespace Arglib {

Value::Value(): refCount(0) {}

Value::~Value() {}

void Value::grab() {
	refCount++;
}

void Value::drop() {
	refCount--;
	if (refCount <= 0) {
		delete this;
	}
}

} // End namespace Arglib

