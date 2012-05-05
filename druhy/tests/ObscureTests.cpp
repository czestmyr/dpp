#include "ObscureTests.h"

#include "Tests.h"
#include "ArgList.h"
#include "Arglib.h"
#include <iostream>

using namespace std;

void ObscureTests::prepareTests() {
	Tests& testSet = Tests::inst();
	testSet.addTest(&ObscureTests::sameOptionTwiceTest, "Adding the same option twice should throw an exception");
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

