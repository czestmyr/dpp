#include "Value.h"

Value::Value(): valid(false) {}

int Value::getInt() { 
	return i;
}

unsigned int Value::getUnsignedInt() {
	return ui;
}

long Value::getLong() {
	return l;
}

unsigned long Value::getUnsignedLong() {
	return ul;
}

float Value::getFloat() {
	return f;
}

double Value::getDouble() {
	return d;
}

void Value::setInt(int newValue) {
	valid = true;
	i = newValue;
}

void Value::setUnsignedInt(unsigned int newValue) {
	valid = true;
	ui = newValue;
}

void Value::setLong(long newValue) {
	valid = true;
	l = newValue;
}

void Value::setUnsignedLong(unsigned long newValue) {
	valid = true;
	ul = newValue;
}

void Value::setFloat(float newValue) {
	valid = true;
	f = newValue;
}

void Value::setDouble(double newValue) {
	valid = true;
	d = newValue;
}

void Value::setPointer(void* pointer) {
	valid = true;
	ptr = pointer;
}

