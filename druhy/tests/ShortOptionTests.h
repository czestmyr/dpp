#ifndef _ARGLIB_SHORT_OPTION_TESTS_H_
#define _ARGLIB_SHORT_OPTION_TESTS_H_

class Tests;

class ShortOptionTests {
	public:
		/// Adds the use cases to the given test set.
		static void addTestsTo(Tests* testSet);

	private:
		static bool definedShortOptionTest();
		static bool undefinedShortOptionTest();
		static bool shortSynonymTest();
};

#endif

