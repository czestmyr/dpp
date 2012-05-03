#include "ValueHandle.h"
ValueHandle::ValueHandle() {
	valuePtr = NULL;	
}
ValueHandle::ValueHandle(const ValueHandle& other) {
	valuePtr->grab();
}
ValueHandle::operator=(const ValueHandle& other) {
	valuePtr->grab();
}
void ValueHandle::setValue(Value* newValue) {
	if(valuePtr!=NULL){
		// We already point to some value
		valuePtr->drop();
	}
	valuePtr = newValue;
	valuePtr->grab();
}
