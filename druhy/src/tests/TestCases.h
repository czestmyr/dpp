#ifndef _ARGLIB_TEST_CASES_H_
#define _ARGLIB_TEST_CASES_H_

#include "../FrontEnd.h"
#include "AbstractTest.h"

class Tests;

class TestCases {
	public:
		/// Adds the test cases to the given test set.
		static void addTestsTo(Tests* testSet);

	private:
		class UseCaseShortOptionTest : public AbstractTest {
			public:
				~UseCaseShortOptionTest() {};
				bool runTest();
				const char* getDescription();
			private:
		};
};

#endif
