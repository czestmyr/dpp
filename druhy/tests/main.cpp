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
	tests.runTests();
	return 0;
}

