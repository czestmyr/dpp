#include "ObscureTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void ObscureTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&ObscureTests::sameOptionTwiceTest, "Adding the same option twice should throw an exception");
	testSet.addTest(&ObscureTests::twoCallsOfParseFunctionTest, "Options parsed in last call should be reset in the new call of parse");
}

bool ObscureTests::sameOptionTwiceTest() {
	FrontEnd arglib;
	arglib.addOption("i");

	try {
		arglib.addOption("i");
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool ObscureTests::twoCallsOfParseFunctionTest() {
	// TODO: implement
	// // should test if status is reset before second call of that function
	return false;
}
