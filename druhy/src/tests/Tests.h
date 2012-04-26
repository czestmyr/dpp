#ifndef _ARGLIB_TESTS_H_
#define _ARGLIB_TESTS_H_

#include <vector>
#include "UseCaseShortOptionTest.h"

class Tests {
	public:
		void runTests();
	private:	
	std::vector<AbstractTest* > tests;	
};

#endif
