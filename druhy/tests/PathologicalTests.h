#ifndef _ARGLIB_PATHOLOGICAL_TESTS_H_
#define _ARGLIB_PATHOLOGICAL_TESTS_H_

class Tests;

/// This test class contains tests for various obscure cases when the input is incorrect
class PathologicalTests {
	public:
		static void prepareTests();

	private:
		static bool sameOptionTwiceTest();
		static bool sameSynonymTwiceTest();
		static bool synonymSameAsOriginalTest();
		static bool undefinedOptionSetHelpTest();
		static bool requiredOptionNotSetTest();
		static bool twoCallsOfParseFunctionTest();
		static bool twoCallsOfParseFunctionArgumentsTest();
		static bool wrongOptionSynonymCallOrder();
		
};

#endif

