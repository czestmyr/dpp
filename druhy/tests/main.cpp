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
		return 0;
	} else {
		return 1;
	}
}

