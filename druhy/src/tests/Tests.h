#ifndef _ARGLIB_TESTS_H_
#define _ARGLIB_TESTS_H_

#include <vector>
#include "AbstractTest.h"

class Tests {
	public:
		/// Returns the singleton instance of the testing class.
		static Tests& inst();

		/// Initializes all the test instances.
		Tests();

		/// Destroys all the held test instances.
		~Tests();

		/// Adds a new test to be performed. The ownership of the
		/// parameter is handed over to the Tests class.
		void addTest(AbstractTest* test);

		/// Runs all the tests that have been registered so far.
		void runTests();
	private:	
		std::vector<AbstractTest*> tests;

		static Tests instance;
};

#endif
