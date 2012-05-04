#ifndef _ARGLIB_ARG_LIST_H_
#define _ARGLIB_ARG_LIST_H_

#include <iostream>

// TODO: document that thic class does not copy the strings. It is just a container of const char pointers.
// Therefore, only immutable strings must be passed to it

class ArgList {
	public:
		ArgList();
		~ArgList();

		ArgList& push(const char* argument);
		const char** getArguments() const;
		int getCount() const;

		/// Debugging function
		void dump(std::ostream& stream);
	private:
		ArgList(const ArgList& other) {};

		void alloc(int size);
		void realloc(int size);
		void dealloc();

		const char** array;
		int currentCount;
		int arraySize;
};

#endif

