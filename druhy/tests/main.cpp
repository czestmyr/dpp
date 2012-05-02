#include "Tests.h"
#include "UseCases.h"
#include "ShortOptionTests.h"
#include "IntegerTests.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	Tests& tests = Tests::inst();

	// Add the tests
	UseCases::addTestsTo(&tests);
	ShortOptionTests::addTestsTo(&tests);
	IntegerTests::addTestsTo(&tests);

	tests.runTests();
	return 0;
}

