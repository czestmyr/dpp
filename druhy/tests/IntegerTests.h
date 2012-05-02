#ifndef _ARGLIB_INTEGER_TESTS_H_
#define _ARGLIB_INTEGER_TESTS_H_

class Tests;

class IntegerTests {
	public:
		/// Adds the use cases to the given test set.
		static void addTestsTo(Tests* testSet);

	private:
		static bool upperLimitTest();
		static bool lowerLimitTest();
		static bool unlimitedTest();
		static bool correctTest();
		static bool malformedTest();
};

#endif

