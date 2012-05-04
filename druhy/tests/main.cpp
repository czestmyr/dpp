#include "Tests.h"
#include "UseCases.h"
#include "ShortOptionTests.h"
#include "IntegerTests.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	// Prepare the tests
	UseCases::prepareTests();
	ShortOptionTests::prepareTests();
	IntegerTests::prepareTests();

	Tests& tests = Tests::inst();
	if (tests.runTests()) {
		cout << "All tests passed!" << endl;
		return 0;
	} else {
		cout << "One or more tests failed!" << endl;
		return 1;
	}
}

