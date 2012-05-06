#include "Tests.h"
#include "Arglib.h"
#include "ArgList.h"

#include <iostream>

using namespace std;

#ifdef COLORS
	#define GREEN_BEGIN "\e[0;32m"
	#define RED_BEGIN "\e[0;31m"
	#define COLOR_END "\e[0m"
#else
	#define GREEN_BEGIN ""
	#define RED_BEGIN ""
	#define COLOR_END ""
#endif

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
			cout << endl << "\t" << GREEN_BEGIN << "Test " << (i+1) << "/" << tests.size() << " OK" << COLOR_END << endl;
		} else {
			cout << endl << "\t" << RED_BEGIN << "Test " << (i+1) << "/" << tests.size() << " FAILED" << COLOR_END << endl;
			success = false;
		}
	}

	if (success) {
		cout << GREEN_BEGIN << "All tests passed!" << COLOR_END << endl;
	} else {
		cout << RED_BEGIN << "Some tests failed!" << COLOR_END << endl;
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
