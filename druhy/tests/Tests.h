#ifndef _ARGLIB_TESTS_H_
#define _ARGLIB_TESTS_H_

#include <vector>
#include <string>

#include "TestFunction.h"

class Tests {
	public:
		/// Returns the singleton instance of the testing class.
		static Tests& inst();

		/// Adds a new test to be performed.
		void addTest(TestFunctionPtr test, const char* testDescription);

		/// Runs all the tests that have been registered so far.
		void runTests();

	private:
		std::vector<TestFunctionPtr> tests;
		std::vector<std::string> testDescriptions;

		static Tests instance;
};

#endif
