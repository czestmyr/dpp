#ifndef _ARGLIB_INTEGER_TESTS_H_
#define _ARGLIB_INTEGER_TESTS_H_

class Tests;

class IntegerTests {
	public:
		static void prepareTests();

	private:
		static bool upperLimitTest();
		static bool lowerLimitTest();
		static bool unlimitedTest();
		static bool overflowTest();
		static bool correctTest();
		static bool malformedTest();
};

#endif

