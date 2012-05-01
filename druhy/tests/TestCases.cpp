#include "TestCases.h"

#include "Tests.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void TestCases::addTestsTo(Tests* testSet) {
	testSet->addTest(new UseCaseShortOptionTest);
}

bool TestCases::UseCaseShortOptionTest::runTest() {
	const char* arg1 = "-v";
	const char* arg2 = "-u";
	const char* arg3 = "-p";
	const char* arg4 = "20";
	const char* argv[4];
	argv[0] = arg1;
	argv[1] = arg2;
	argv[2] = arg3;
	argv[3] = arg4;

	try {
		FrontEnd h;
		h.addOption("v");
		h.addSynonym("v","u");

		Integer* integer = new Integer;
		integer->setHighBound(100);
		integer->setLowBound(0);
		h.addOption("p", REQUIRED, integer, "Help for the integer option");

		h.parse(4,argv);
	} catch (ArgumentException e) {
		cout << e.what();
		return false;
	}

	return true;
}

const char* TestCases::UseCaseShortOptionTest::getDescription() {
	return "Short option use case (should not throw anything): \"-v -u -p 20\"";
}

