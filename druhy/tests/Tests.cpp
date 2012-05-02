#include "Tests.h"
#include "Arglib.h"
#include "ArgList.h"

#include <iostream>

using namespace std;

Tests& Tests::inst() {
	return instance;
}

void Tests::addTest(TestFunctionPtr test, const char* testDescription) {
	tests.push_back(test);
	testDescriptions.push_back(testDescription);
}

bool Tests::runTests(){
	cout << "Running tests..." << endl;
	bool success = true;

	for (int i = 0; i < tests.size(); ++i) {
		cout << "\tTest " << (i+1) << "/" << tests.size() << ": ";
		cout << testDescriptions[i] << " | ";

		if (tests[i]()) {
			cout << " ... OK." << endl;
		} else {
			cout << " ... FAIL!" << endl;
			success = false;
		}
	}

	return success;
}

bool Tests::parseMustThrow(FrontEnd& arglib, const ArgList& arguments) {
	try {
		arglib.parse(arguments.getCount(), arguments.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return true;
	}

	return false;
}

bool Tests::parseMustNotThrow(FrontEnd& arglib, const ArgList& arguments) {
	try {
		arglib.parse(arguments.getCount(), arguments.getArguments());
	} catch (ArgumentException e) {
		cout << "Exception: " << e.what();
		return false;
	}

	return true;
}

Tests Tests::instance = Tests();
