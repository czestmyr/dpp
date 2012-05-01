#include "Tests.h"
#include "UseCases.h"
#include "ShortOptions.h"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	Tests& tests = Tests::inst();

	// Add the tests
	UseCases::addTestsTo(&tests);
	ShortOptions::addTestsTo(&tests);

	tests.runTests();
	return 0;
}

