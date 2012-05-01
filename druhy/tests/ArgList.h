#ifndef _ARGLIB_ARG_LIST_H_
#define _ARGLIB_ARG_LIST_H_

class ArgList {
	public:
		ArgList();
		~ArgList();

		ArgList& push(const char* argument);
		const char** getArguments();
		int getCount();

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

