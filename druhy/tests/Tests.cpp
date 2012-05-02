#include "Tests.h"

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

Tests Tests::instance = Tests();
