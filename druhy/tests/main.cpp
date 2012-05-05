#include "Tests.h"
#include "UseCases.h"
#include "ShortOptionTests.h"
#include "IntegerTests.h"
#include "PathologicalTests.h"
#include "StringTests.h"
#include "BoolTests.h"
#include "EnumTests.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	// Prepare the tests
	PathologicalTests::prepareTests();
	ShortOptionTests::prepareTests();
	IntegerTests::prepareTests();
	StringTests::prepareTests();
	BoolTests::prepareTests();
	UseCases::prepareTests();
	EnumTests::prepareTests();

	Tests& tests = Tests::inst();
	if (tests.runTests()) {
		cout << "All tests passed!" << endl;
		return 0;
	} else {
		cout << "One or more tests failed!" << endl;
		return 1;
	}
}

