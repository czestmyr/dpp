#ifndef _ARGLIB_BOOL_TESTS_H_
#define _ARGLIB_BOOL_TESTS_H_

class Tests;

class BoolTests {
	public:
		static void prepareTests();

	private:
		static bool trueFalseTest();
		static bool badInputTest();
		static bool noInputTest();
};

#endif

