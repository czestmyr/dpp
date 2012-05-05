#include "ArgList.h"

#define BASE_SIZE 8

ArgList::ArgList() {
	currentCount = 0;
	alloc(BASE_SIZE);
}

ArgList::~ArgList() {
	dealloc();
}

ArgList& ArgList::push(const char* argument) {
	if (currentCount == arraySize) {
		realloc(arraySize*2);
	}

	array[currentCount] = argument;
	currentCount++;

	return *this;
}

const char** ArgList::getArguments() const {
	return array;
}

int ArgList::getCount() const {
	return currentCount;
}

void ArgList::dump(std::ostream& stream) {
	for (int i = 0; i < currentCount; ++i) {
		stream << "\"" << array[i] << "\" ";
	}
	stream << "| ";
}

void ArgList::alloc(int size) {
	array = new const char*[size];
	arraySize = size;
}
		
void ArgList::realloc(int size) {
	const char** oldArray = array;
	int oldArraySize = arraySize;
	alloc(size);

	for (int i = 0; i < oldArraySize; ++i) {
		array[i] = oldArray[i];
	}
	delete[] oldArray;
}

void ArgList::dealloc() {
	delete[] array;
}

