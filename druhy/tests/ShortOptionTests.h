#ifndef _ARGLIB_SHORT_OPTION_TESTS_H_
#define _ARGLIB_SHORT_OPTION_TESTS_H_

class Tests;

class ShortOptionTests {
	public:
		static void prepareTests();

	private:
		static bool definedShortOptionTest();
		static bool undefinedShortOptionTest();
		static bool shortSynonymTest();
};

#endif

